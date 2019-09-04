#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_2__* dentry; TYPE_3__* mnt; } ;
struct TYPE_6__ {TYPE_2__* mnt_root; } ;
struct TYPE_5__ {TYPE_1__* d_sb; } ;
struct TYPE_4__ {scalar_t__ s_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 scalar_t__ AUTOFS_SUPER_MAGIC ; 
 int ENOENT ; 
 int /*<<< orphan*/  follow_up (struct path*) ; 
 int kern_path_mountpoint (int /*<<< orphan*/ ,char const*,struct path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_get (struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 

__attribute__((used)) static int find_autofs_mount(const char *pathname,
			     struct path *res,
			     int test(const struct path *path, void *data),
			     void *data)
{
	struct path path;
	int err;

	err = kern_path_mountpoint(AT_FDCWD, pathname, &path, 0);
	if (err)
		return err;
	err = -ENOENT;
	while (path.dentry == path.mnt->mnt_root) {
		if (path.dentry->d_sb->s_magic == AUTOFS_SUPER_MAGIC) {
			if (test(&path, data)) {
				path_get(&path);
				*res = path;
				err = 0;
				break;
			}
		}
		if (!follow_up(&path))
			break;
	}
	path_put(&path);
	return err;
}