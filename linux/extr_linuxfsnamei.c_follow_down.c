#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int /*<<< orphan*/  mnt_root; } ;
struct path {TYPE_2__* dentry; struct vfsmount* mnt; } ;
struct TYPE_5__ {TYPE_1__* d_op; int /*<<< orphan*/  d_flags; } ;
struct TYPE_4__ {int (* d_manage ) (struct path*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int DCACHE_MANAGED_DENTRY ; 
 unsigned int DCACHE_MANAGE_TRANSIT ; 
 unsigned int DCACHE_MOUNTED ; 
 int EISDIR ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 TYPE_2__* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (TYPE_2__*) ; 
 struct vfsmount* lookup_mnt (struct path*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int stub1 (struct path*,int) ; 
 int /*<<< orphan*/  unlikely (unsigned int) ; 

int follow_down(struct path *path)
{
	unsigned managed;
	int ret;

	while (managed = READ_ONCE(path->dentry->d_flags),
	       unlikely(managed & DCACHE_MANAGED_DENTRY)) {
		/* Allow the filesystem to manage the transit without i_mutex
		 * being held.
		 *
		 * We indicate to the filesystem if someone is trying to mount
		 * something here.  This gives autofs the chance to deny anyone
		 * other than its daemon the right to mount on its
		 * superstructure.
		 *
		 * The filesystem may sleep at this point.
		 */
		if (managed & DCACHE_MANAGE_TRANSIT) {
			BUG_ON(!path->dentry->d_op);
			BUG_ON(!path->dentry->d_op->d_manage);
			ret = path->dentry->d_op->d_manage(path, false);
			if (ret < 0)
				return ret == -EISDIR ? 0 : ret;
		}

		/* Transit to a mounted filesystem. */
		if (managed & DCACHE_MOUNTED) {
			struct vfsmount *mounted = lookup_mnt(path);
			if (!mounted)
				break;
			dput(path->dentry);
			mntput(path->mnt);
			path->mnt = mounted;
			path->dentry = dget(mounted->mnt_root);
			continue;
		}

		/* Don't handle automount points here */
		break;
	}
	return 0;
}