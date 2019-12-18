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
struct cifs_sb_info {int /*<<< orphan*/  local_nls; } ;
struct cifsInodeInfo {int cifsAttrs; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_4__ {int /*<<< orphan*/  Attributes; } ;
typedef  TYPE_1__ FILE_BASIC_INFO ;

/* Variables and functions */
 int ATTR_READONLY ; 
 int CIFSSMBSetPathInfo (unsigned int const,struct cifs_tcon*,char const*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cifsInodeInfo* CIFS_I (struct inode*) ; 
 int /*<<< orphan*/  cifs_remap (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cifs_mkdir_setinfo(struct inode *inode, const char *full_path,
		   struct cifs_sb_info *cifs_sb, struct cifs_tcon *tcon,
		   const unsigned int xid)
{
	FILE_BASIC_INFO info;
	struct cifsInodeInfo *cifsInode;
	u32 dosattrs;
	int rc;

	memset(&info, 0, sizeof(info));
	cifsInode = CIFS_I(inode);
	dosattrs = cifsInode->cifsAttrs|ATTR_READONLY;
	info.Attributes = cpu_to_le32(dosattrs);
	rc = CIFSSMBSetPathInfo(xid, tcon, full_path, &info, cifs_sb->local_nls,
				cifs_remap(cifs_sb));
	if (rc == 0)
		cifsInode->cifsAttrs = dosattrs;
}