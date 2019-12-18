#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; } ;
struct cifs_sb_info {int dummy; } ;
struct TCP_Server_Info {TYPE_2__* ops; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_9__ {TYPE_1__* ses; } ;
struct TYPE_8__ {int /*<<< orphan*/  Attributes; scalar_t__ CreationTime; void* ChangeTime; void* LastWriteTime; void* LastAccessTime; scalar_t__ Pad; } ;
struct TYPE_7__ {int (* set_file_info ) (struct inode*,char*,TYPE_3__*,unsigned int) ;} ;
struct TYPE_6__ {struct TCP_Server_Info* server; } ;
typedef  TYPE_3__ FILE_BASIC_INFO ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_CTIME ; 
 int ATTR_MTIME ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  cifs_UnixTimeToNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int stub1 (struct inode*,char*,TYPE_3__*,unsigned int) ; 

int
cifs_set_file_info(struct inode *inode, struct iattr *attrs, unsigned int xid,
		   char *full_path, __u32 dosattr)
{
	bool set_time = false;
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct TCP_Server_Info *server;
	FILE_BASIC_INFO	info_buf;

	if (attrs == NULL)
		return -EINVAL;

	server = cifs_sb_master_tcon(cifs_sb)->ses->server;
	if (!server->ops->set_file_info)
		return -ENOSYS;

	info_buf.Pad = 0;

	if (attrs->ia_valid & ATTR_ATIME) {
		set_time = true;
		info_buf.LastAccessTime =
			cpu_to_le64(cifs_UnixTimeToNT(attrs->ia_atime));
	} else
		info_buf.LastAccessTime = 0;

	if (attrs->ia_valid & ATTR_MTIME) {
		set_time = true;
		info_buf.LastWriteTime =
		    cpu_to_le64(cifs_UnixTimeToNT(attrs->ia_mtime));
	} else
		info_buf.LastWriteTime = 0;

	/*
	 * Samba throws this field away, but windows may actually use it.
	 * Do not set ctime unless other time stamps are changed explicitly
	 * (i.e. by utimes()) since we would then have a mix of client and
	 * server times.
	 */
	if (set_time && (attrs->ia_valid & ATTR_CTIME)) {
		cifs_dbg(FYI, "CIFS - CTIME changed\n");
		info_buf.ChangeTime =
		    cpu_to_le64(cifs_UnixTimeToNT(attrs->ia_ctime));
	} else
		info_buf.ChangeTime = 0;

	info_buf.CreationTime = 0;	/* don't change */
	info_buf.Attributes = cpu_to_le32(dosattr);

	return server->ops->set_file_info(inode, full_path, &info_buf, xid);
}