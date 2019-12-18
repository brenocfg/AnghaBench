#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct smb_hdr {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  num_mkdirs; } ;
struct TYPE_9__ {TYPE_2__ cifs_stats; } ;
struct cifs_tcon {TYPE_3__ stats; int /*<<< orphan*/  ses; } ;
struct cifs_sb_info {int /*<<< orphan*/  local_nls; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_7__ {int Flags2; } ;
struct TYPE_10__ {int BufferFormat; int /*<<< orphan*/  ByteCount; scalar_t__ DirName; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  CREATE_DIRECTORY_RSP ;
typedef  TYPE_4__ CREATE_DIRECTORY_REQ ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int SMBFLG2_UNICODE ; 
 int /*<<< orphan*/  SMB_COM_CREATE_DIRECTORY ; 
 int SendReceive (unsigned int const,int /*<<< orphan*/ ,struct smb_hdr*,struct smb_hdr*,int*,int /*<<< orphan*/ ) ; 
 int cifsConvertToUTF16 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cifs_buf_release (TYPE_4__*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int cifs_remap (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_stats_inc (int /*<<< orphan*/ *) ; 
 int copy_path_name (scalar_t__,char const*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  inc_rfc1001_len (TYPE_4__*,int) ; 
 int smb_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cifs_tcon*,void**,void**) ; 

int
CIFSSMBMkDir(const unsigned int xid, struct inode *inode, umode_t mode,
	     struct cifs_tcon *tcon, const char *name,
	     struct cifs_sb_info *cifs_sb)
{
	int rc = 0;
	CREATE_DIRECTORY_REQ *pSMB = NULL;
	CREATE_DIRECTORY_RSP *pSMBr = NULL;
	int bytes_returned;
	int name_len;
	int remap = cifs_remap(cifs_sb);

	cifs_dbg(FYI, "In CIFSSMBMkDir\n");
MkDirRetry:
	rc = smb_init(SMB_COM_CREATE_DIRECTORY, 0, tcon, (void **) &pSMB,
		      (void **) &pSMBr);
	if (rc)
		return rc;

	if (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) {
		name_len = cifsConvertToUTF16((__le16 *) pSMB->DirName, name,
					      PATH_MAX, cifs_sb->local_nls,
					      remap);
		name_len++;	/* trailing null */
		name_len *= 2;
	} else {
		name_len = copy_path_name(pSMB->DirName, name);
	}

	pSMB->BufferFormat = 0x04;
	inc_rfc1001_len(pSMB, name_len + 1);
	pSMB->ByteCount = cpu_to_le16(name_len + 1);
	rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
			 (struct smb_hdr *) pSMBr, &bytes_returned, 0);
	cifs_stats_inc(&tcon->stats.cifs_stats.num_mkdirs);
	if (rc)
		cifs_dbg(FYI, "Error in Mkdir = %d\n", rc);

	cifs_buf_release(pSMB);
	if (rc == -EAGAIN)
		goto MkDirRetry;
	return rc;
}