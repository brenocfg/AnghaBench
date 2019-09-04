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
struct smb_hdr {int dummy; } ;
struct TYPE_2__ {int Flags2; int /*<<< orphan*/  Protocol; } ;
struct smb_com_transaction_ioctl_rsp {TYPE_1__ hdr; int /*<<< orphan*/  ByteCount; int /*<<< orphan*/  DataCount; int /*<<< orphan*/  DataOffset; } ;
struct smb_com_transaction_ioctl_req {int MaxSetupCount; int SetupCount; int IsFsctl; scalar_t__ ByteCount; int /*<<< orphan*/  Fid; scalar_t__ IsRootFlag; scalar_t__ FunctionCode; scalar_t__ TotalParameterCount; scalar_t__ ParameterCount; int /*<<< orphan*/  SubCommand; scalar_t__ DataOffset; scalar_t__ DataCount; scalar_t__ ParameterOffset; scalar_t__ Reserved; scalar_t__ MaxDataCount; scalar_t__ MaxParameterCount; scalar_t__ TotalDataCount; } ;
struct reparse_symlink_data {scalar_t__ ReparseTag; char* PathBuffer; int /*<<< orphan*/  SubstituteNameLength; int /*<<< orphan*/  SubstituteNameOffset; int /*<<< orphan*/  ReparseDataLength; } ;
struct reparse_posix_data {scalar_t__ InodeType; char* PathBuffer; } ;
struct nls_table {int dummy; } ;
struct cifs_tcon {int /*<<< orphan*/  ses; } ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int CIFSMaxBufSize ; 
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int FSCTL_GET_REPARSE_POINT ; 
 int /*<<< orphan*/  FYI ; 
 int IO_REPARSE_TAG_NFS ; 
 int IO_REPARSE_TAG_SYMLINK ; 
 int /*<<< orphan*/  NFS_SPECFILE_LNK ; 
 int /*<<< orphan*/  NT_TRANSACT_IOCTL ; 
 int SMBFLG2_UNICODE ; 
 int /*<<< orphan*/  SMB_COM_NT_TRANSACT ; 
 int SendReceive (unsigned int const,int /*<<< orphan*/ ,struct smb_hdr*,struct smb_hdr*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_buf_release (struct smb_com_transaction_ioctl_req*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 char* cifs_strndup_from_utf16 (char*,unsigned int,int,struct nls_table const*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_le32 (int) ; 
 scalar_t__ cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int get_bcc (TYPE_1__*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (scalar_t__) ; 
 int smb_init (int /*<<< orphan*/ ,int,struct cifs_tcon*,void**,void**) ; 

int
CIFSSMBQuerySymLink(const unsigned int xid, struct cifs_tcon *tcon,
		    __u16 fid, char **symlinkinfo,
		    const struct nls_table *nls_codepage)
{
	int rc = 0;
	int bytes_returned;
	struct smb_com_transaction_ioctl_req *pSMB;
	struct smb_com_transaction_ioctl_rsp *pSMBr;
	bool is_unicode;
	unsigned int sub_len;
	char *sub_start;
	struct reparse_symlink_data *reparse_buf;
	struct reparse_posix_data *posix_buf;
	__u32 data_offset, data_count;
	char *end_of_smb;

	cifs_dbg(FYI, "In Windows reparse style QueryLink for fid %u\n", fid);
	rc = smb_init(SMB_COM_NT_TRANSACT, 23, tcon, (void **) &pSMB,
		      (void **) &pSMBr);
	if (rc)
		return rc;

	pSMB->TotalParameterCount = 0 ;
	pSMB->TotalDataCount = 0;
	pSMB->MaxParameterCount = cpu_to_le32(2);
	/* BB find exact data count max from sess structure BB */
	pSMB->MaxDataCount = cpu_to_le32(CIFSMaxBufSize & 0xFFFFFF00);
	pSMB->MaxSetupCount = 4;
	pSMB->Reserved = 0;
	pSMB->ParameterOffset = 0;
	pSMB->DataCount = 0;
	pSMB->DataOffset = 0;
	pSMB->SetupCount = 4;
	pSMB->SubCommand = cpu_to_le16(NT_TRANSACT_IOCTL);
	pSMB->ParameterCount = pSMB->TotalParameterCount;
	pSMB->FunctionCode = cpu_to_le32(FSCTL_GET_REPARSE_POINT);
	pSMB->IsFsctl = 1; /* FSCTL */
	pSMB->IsRootFlag = 0;
	pSMB->Fid = fid; /* file handle always le */
	pSMB->ByteCount = 0;

	rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
			 (struct smb_hdr *) pSMBr, &bytes_returned, 0);
	if (rc) {
		cifs_dbg(FYI, "Send error in QueryReparseLinkInfo = %d\n", rc);
		goto qreparse_out;
	}

	data_offset = le32_to_cpu(pSMBr->DataOffset);
	data_count = le32_to_cpu(pSMBr->DataCount);
	if (get_bcc(&pSMBr->hdr) < 2 || data_offset > 512) {
		/* BB also check enough total bytes returned */
		rc = -EIO;	/* bad smb */
		goto qreparse_out;
	}
	if (!data_count || (data_count > 2048)) {
		rc = -EIO;
		cifs_dbg(FYI, "Invalid return data count on get reparse info ioctl\n");
		goto qreparse_out;
	}
	end_of_smb = 2 + get_bcc(&pSMBr->hdr) + (char *)&pSMBr->ByteCount;
	reparse_buf = (struct reparse_symlink_data *)
				((char *)&pSMBr->hdr.Protocol + data_offset);
	if ((char *)reparse_buf >= end_of_smb) {
		rc = -EIO;
		goto qreparse_out;
	}
	if (reparse_buf->ReparseTag == cpu_to_le32(IO_REPARSE_TAG_NFS)) {
		cifs_dbg(FYI, "NFS style reparse tag\n");
		posix_buf =  (struct reparse_posix_data *)reparse_buf;

		if (posix_buf->InodeType != cpu_to_le64(NFS_SPECFILE_LNK)) {
			cifs_dbg(FYI, "unsupported file type 0x%llx\n",
				 le64_to_cpu(posix_buf->InodeType));
			rc = -EOPNOTSUPP;
			goto qreparse_out;
		}
		is_unicode = true;
		sub_len = le16_to_cpu(reparse_buf->ReparseDataLength);
		if (posix_buf->PathBuffer + sub_len > end_of_smb) {
			cifs_dbg(FYI, "reparse buf beyond SMB\n");
			rc = -EIO;
			goto qreparse_out;
		}
		*symlinkinfo = cifs_strndup_from_utf16(posix_buf->PathBuffer,
				sub_len, is_unicode, nls_codepage);
		goto qreparse_out;
	} else if (reparse_buf->ReparseTag !=
			cpu_to_le32(IO_REPARSE_TAG_SYMLINK)) {
		rc = -EOPNOTSUPP;
		goto qreparse_out;
	}

	/* Reparse tag is NTFS symlink */
	sub_start = le16_to_cpu(reparse_buf->SubstituteNameOffset) +
				reparse_buf->PathBuffer;
	sub_len = le16_to_cpu(reparse_buf->SubstituteNameLength);
	if (sub_start + sub_len > end_of_smb) {
		cifs_dbg(FYI, "reparse buf beyond SMB\n");
		rc = -EIO;
		goto qreparse_out;
	}
	if (pSMBr->hdr.Flags2 & SMBFLG2_UNICODE)
		is_unicode = true;
	else
		is_unicode = false;

	/* BB FIXME investigate remapping reserved chars here */
	*symlinkinfo = cifs_strndup_from_utf16(sub_start, sub_len, is_unicode,
					       nls_codepage);
	if (!*symlinkinfo)
		rc = -ENOMEM;
qreparse_out:
	cifs_buf_release(pSMB);

	/*
	 * Note: On -EAGAIN error only caller can retry on handle based calls
	 * since file handle passed in no longer valid.
	 */
	return rc;
}