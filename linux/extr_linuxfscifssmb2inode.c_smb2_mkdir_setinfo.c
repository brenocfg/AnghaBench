#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct inode {int dummy; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int dummy; } ;
struct cifsInodeInfo {int cifsAttrs; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_4__ {int /*<<< orphan*/  Attributes; } ;
typedef  TYPE_1__ FILE_BASIC_INFO ;

/* Variables and functions */
 int ATTR_READONLY ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  CREATE_NOT_FILE ; 
 int /*<<< orphan*/  FILE_CREATE ; 
 int /*<<< orphan*/  FILE_WRITE_ATTRIBUTES ; 
 int /*<<< orphan*/  SMB2_OP_SET_INFO ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int smb2_open_op_close (unsigned int const,struct cifs_tcon*,struct cifs_sb_info*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

void
smb2_mkdir_setinfo(struct inode *inode, const char *name,
		   struct cifs_sb_info *cifs_sb, struct cifs_tcon *tcon,
		   const unsigned int xid)
{
	FILE_BASIC_INFO data;
	struct cifsInodeInfo *cifs_i;
	u32 dosattrs;
	int tmprc;

	memset(&data, 0, sizeof(data));
	cifs_i = CIFS_I(inode);
	dosattrs = cifs_i->cifsAttrs | ATTR_READONLY;
	data.Attributes = cpu_to_le32(dosattrs);
	tmprc = smb2_open_op_close(xid, tcon, cifs_sb, name,
				   FILE_WRITE_ATTRIBUTES, FILE_CREATE,
				   CREATE_NOT_FILE, &data, SMB2_OP_SET_INFO);
	if (tmprc == 0)
		cifs_i->cifsAttrs = dosattrs;
}