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
struct smb_hdr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  num_renames; } ;
struct TYPE_9__ {TYPE_2__ cifs_stats; } ;
struct cifs_tcon {TYPE_3__ stats; int /*<<< orphan*/  ses; } ;
struct cifs_sb_info {int /*<<< orphan*/  local_nls; } ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_7__ {int Flags2; } ;
struct TYPE_10__ {int BufferFormat; int* OldFileName; void* ByteCount; TYPE_1__ hdr; void* SearchAttributes; } ;
typedef  int /*<<< orphan*/  RENAME_RSP ;
typedef  TYPE_4__ RENAME_REQ ;

/* Variables and functions */
 int ATTR_DIRECTORY ; 
 int ATTR_HIDDEN ; 
 int ATTR_READONLY ; 
 int ATTR_SYSTEM ; 
 int EAGAIN ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int SMBFLG2_UNICODE ; 
 int /*<<< orphan*/  SMB_COM_RENAME ; 
 int SendReceive (unsigned int const,int /*<<< orphan*/ ,struct smb_hdr*,struct smb_hdr*,int*,int /*<<< orphan*/ ) ; 
 int cifsConvertToUTF16 (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cifs_buf_release (TYPE_4__*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int cifs_remap (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_stats_inc (int /*<<< orphan*/ *) ; 
 int copy_path_name (int*,char const*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  inc_rfc1001_len (TYPE_4__*,int) ; 
 int smb_init (int /*<<< orphan*/ ,int,struct cifs_tcon*,void**,void**) ; 

int
CIFSSMBRename(const unsigned int xid, struct cifs_tcon *tcon,
	      const char *from_name, const char *to_name,
	      struct cifs_sb_info *cifs_sb)
{
	int rc = 0;
	RENAME_REQ *pSMB = NULL;
	RENAME_RSP *pSMBr = NULL;
	int bytes_returned;
	int name_len, name_len2;
	__u16 count;
	int remap = cifs_remap(cifs_sb);

	cifs_dbg(FYI, "In CIFSSMBRename\n");
renameRetry:
	rc = smb_init(SMB_COM_RENAME, 1, tcon, (void **) &pSMB,
		      (void **) &pSMBr);
	if (rc)
		return rc;

	pSMB->BufferFormat = 0x04;
	pSMB->SearchAttributes =
	    cpu_to_le16(ATTR_READONLY | ATTR_HIDDEN | ATTR_SYSTEM |
			ATTR_DIRECTORY);

	if (pSMB->hdr.Flags2 & SMBFLG2_UNICODE) {
		name_len = cifsConvertToUTF16((__le16 *) pSMB->OldFileName,
					      from_name, PATH_MAX,
					      cifs_sb->local_nls, remap);
		name_len++;	/* trailing null */
		name_len *= 2;
		pSMB->OldFileName[name_len] = 0x04;	/* pad */
	/* protocol requires ASCII signature byte on Unicode string */
		pSMB->OldFileName[name_len + 1] = 0x00;
		name_len2 =
		    cifsConvertToUTF16((__le16 *)&pSMB->OldFileName[name_len+2],
				       to_name, PATH_MAX, cifs_sb->local_nls,
				       remap);
		name_len2 += 1 /* trailing null */  + 1 /* Signature word */ ;
		name_len2 *= 2;	/* convert to bytes */
	} else {
		name_len = copy_path_name(pSMB->OldFileName, from_name);
		name_len2 = copy_path_name(pSMB->OldFileName+name_len+1, to_name);
		pSMB->OldFileName[name_len] = 0x04;  /* 2nd buffer format */
		name_len2++;	/* signature byte */
	}

	count = 1 /* 1st signature byte */  + name_len + name_len2;
	inc_rfc1001_len(pSMB, count);
	pSMB->ByteCount = cpu_to_le16(count);

	rc = SendReceive(xid, tcon->ses, (struct smb_hdr *) pSMB,
			 (struct smb_hdr *) pSMBr, &bytes_returned, 0);
	cifs_stats_inc(&tcon->stats.cifs_stats.num_renames);
	if (rc)
		cifs_dbg(FYI, "Send error in rename = %d\n", rc);

	cifs_buf_release(pSMB);

	if (rc == -EAGAIN)
		goto renameRetry;

	return rc;
}