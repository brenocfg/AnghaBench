#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int len; char* name; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/  d_sb; } ;
struct TYPE_4__ {scalar_t__ MaxPathNameComponentLength; } ;
struct cifs_tcon {TYPE_2__ fsAttrInfo; } ;
struct cifs_sb_info {int mnt_cifs_flags; } ;

/* Variables and functions */
 int CIFS_MOUNT_POSIX_PATHS ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int le32_to_cpu (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
check_name(struct dentry *direntry, struct cifs_tcon *tcon)
{
	struct cifs_sb_info *cifs_sb = CIFS_SB(direntry->d_sb);
	int i;

	if (unlikely(tcon->fsAttrInfo.MaxPathNameComponentLength &&
		     direntry->d_name.len >
		     le32_to_cpu(tcon->fsAttrInfo.MaxPathNameComponentLength)))
		return -ENAMETOOLONG;

	if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_POSIX_PATHS)) {
		for (i = 0; i < direntry->d_name.len; i++) {
			if (direntry->d_name.name[i] == '\\') {
				cifs_dbg(FYI, "Invalid file name\n");
				return -EINVAL;
			}
		}
	}
	return 0;
}