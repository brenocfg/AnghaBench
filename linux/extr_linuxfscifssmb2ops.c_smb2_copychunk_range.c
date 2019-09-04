#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct copychunk_ioctl_rsp {scalar_t__ Length; scalar_t__ TotalBytesWritten; scalar_t__ ChunksWritten; scalar_t__ ChunkBytesWritten; void* TargetOffset; void* SourceOffset; scalar_t__ Reserved2; scalar_t__ Reserved; void* ChunkCount; } ;
struct copychunk_ioctl {scalar_t__ Length; scalar_t__ TotalBytesWritten; scalar_t__ ChunksWritten; scalar_t__ ChunkBytesWritten; void* TargetOffset; void* SourceOffset; scalar_t__ Reserved2; scalar_t__ Reserved; void* ChunkCount; } ;
struct cifs_tcon {scalar_t__ max_bytes_chunk; } ;
struct TYPE_2__ {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
struct cifsFileInfo {TYPE_1__ fid; int /*<<< orphan*/  tlink; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  FSCTL_SRV_COPYCHUNK_WRITE ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SMB2_ioctl (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,char**,unsigned int*) ; 
 int SMB2_request_res_key (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct copychunk_ioctl_rsp*) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct copychunk_ioctl_rsp*) ; 
 struct copychunk_ioctl_rsp* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 
 int min_t (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct cifs_tcon* tlink_tcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static ssize_t
smb2_copychunk_range(const unsigned int xid,
			struct cifsFileInfo *srcfile,
			struct cifsFileInfo *trgtfile, u64 src_off,
			u64 len, u64 dest_off)
{
	int rc;
	unsigned int ret_data_len;
	struct copychunk_ioctl *pcchunk;
	struct copychunk_ioctl_rsp *retbuf = NULL;
	struct cifs_tcon *tcon;
	int chunks_copied = 0;
	bool chunk_sizes_updated = false;
	ssize_t bytes_written, total_bytes_written = 0;

	pcchunk = kmalloc(sizeof(struct copychunk_ioctl), GFP_KERNEL);

	if (pcchunk == NULL)
		return -ENOMEM;

	cifs_dbg(FYI, "in smb2_copychunk_range - about to call request res key\n");
	/* Request a key from the server to identify the source of the copy */
	rc = SMB2_request_res_key(xid, tlink_tcon(srcfile->tlink),
				srcfile->fid.persistent_fid,
				srcfile->fid.volatile_fid, pcchunk);

	/* Note: request_res_key sets res_key null only if rc !=0 */
	if (rc)
		goto cchunk_out;

	/* For now array only one chunk long, will make more flexible later */
	pcchunk->ChunkCount = cpu_to_le32(1);
	pcchunk->Reserved = 0;
	pcchunk->Reserved2 = 0;

	tcon = tlink_tcon(trgtfile->tlink);

	while (len > 0) {
		pcchunk->SourceOffset = cpu_to_le64(src_off);
		pcchunk->TargetOffset = cpu_to_le64(dest_off);
		pcchunk->Length =
			cpu_to_le32(min_t(u32, len, tcon->max_bytes_chunk));

		/* Request server copy to target from src identified by key */
		rc = SMB2_ioctl(xid, tcon, trgtfile->fid.persistent_fid,
			trgtfile->fid.volatile_fid, FSCTL_SRV_COPYCHUNK_WRITE,
			true /* is_fsctl */, (char *)pcchunk,
			sizeof(struct copychunk_ioctl),	(char **)&retbuf,
			&ret_data_len);
		if (rc == 0) {
			if (ret_data_len !=
					sizeof(struct copychunk_ioctl_rsp)) {
				cifs_dbg(VFS, "invalid cchunk response size\n");
				rc = -EIO;
				goto cchunk_out;
			}
			if (retbuf->TotalBytesWritten == 0) {
				cifs_dbg(FYI, "no bytes copied\n");
				rc = -EIO;
				goto cchunk_out;
			}
			/*
			 * Check if server claimed to write more than we asked
			 */
			if (le32_to_cpu(retbuf->TotalBytesWritten) >
			    le32_to_cpu(pcchunk->Length)) {
				cifs_dbg(VFS, "invalid copy chunk response\n");
				rc = -EIO;
				goto cchunk_out;
			}
			if (le32_to_cpu(retbuf->ChunksWritten) != 1) {
				cifs_dbg(VFS, "invalid num chunks written\n");
				rc = -EIO;
				goto cchunk_out;
			}
			chunks_copied++;

			bytes_written = le32_to_cpu(retbuf->TotalBytesWritten);
			src_off += bytes_written;
			dest_off += bytes_written;
			len -= bytes_written;
			total_bytes_written += bytes_written;

			cifs_dbg(FYI, "Chunks %d PartialChunk %d Total %zu\n",
				le32_to_cpu(retbuf->ChunksWritten),
				le32_to_cpu(retbuf->ChunkBytesWritten),
				bytes_written);
		} else if (rc == -EINVAL) {
			if (ret_data_len != sizeof(struct copychunk_ioctl_rsp))
				goto cchunk_out;

			cifs_dbg(FYI, "MaxChunks %d BytesChunk %d MaxCopy %d\n",
				le32_to_cpu(retbuf->ChunksWritten),
				le32_to_cpu(retbuf->ChunkBytesWritten),
				le32_to_cpu(retbuf->TotalBytesWritten));

			/*
			 * Check if this is the first request using these sizes,
			 * (ie check if copy succeed once with original sizes
			 * and check if the server gave us different sizes after
			 * we already updated max sizes on previous request).
			 * if not then why is the server returning an error now
			 */
			if ((chunks_copied != 0) || chunk_sizes_updated)
				goto cchunk_out;

			/* Check that server is not asking us to grow size */
			if (le32_to_cpu(retbuf->ChunkBytesWritten) <
					tcon->max_bytes_chunk)
				tcon->max_bytes_chunk =
					le32_to_cpu(retbuf->ChunkBytesWritten);
			else
				goto cchunk_out; /* server gave us bogus size */

			/* No need to change MaxChunks since already set to 1 */
			chunk_sizes_updated = true;
		} else
			goto cchunk_out;
	}

cchunk_out:
	kfree(pcchunk);
	kfree(retbuf);
	if (rc)
		return rc;
	else
		return total_bytes_written;
}