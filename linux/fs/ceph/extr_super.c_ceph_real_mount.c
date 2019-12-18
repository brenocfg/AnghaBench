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
struct dentry {int dummy; } ;
struct ceph_fs_client {TYPE_3__* client; int /*<<< orphan*/  mount_state; TYPE_2__* sb; TYPE_1__* mount_options; } ;
struct TYPE_6__ {int /*<<< orphan*/  mount_mutex; } ;
struct TYPE_5__ {struct dentry* s_root; } ;
struct TYPE_4__ {int flags; char* server_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_MOUNT_MOUNTED ; 
 int CEPH_MOUNT_OPT_FSCACHE ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int __ceph_open_session (TYPE_3__*,unsigned long) ; 
 int /*<<< orphan*/  ceph_fs_debugfs_init (struct ceph_fs_client*) ; 
 int ceph_fscache_register_fs (struct ceph_fs_client*) ; 
 void* dget (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dentry* open_root_dentry (struct ceph_fs_client*,char const*,unsigned long) ; 

__attribute__((used)) static struct dentry *ceph_real_mount(struct ceph_fs_client *fsc)
{
	int err;
	unsigned long started = jiffies;  /* note the start time */
	struct dentry *root;

	dout("mount start %p\n", fsc);
	mutex_lock(&fsc->client->mount_mutex);

	if (!fsc->sb->s_root) {
		const char *path;
		err = __ceph_open_session(fsc->client, started);
		if (err < 0)
			goto out;

		/* setup fscache */
		if (fsc->mount_options->flags & CEPH_MOUNT_OPT_FSCACHE) {
			err = ceph_fscache_register_fs(fsc);
			if (err < 0)
				goto out;
		}

		if (!fsc->mount_options->server_path) {
			path = "";
			dout("mount opening path \\t\n");
		} else {
			path = fsc->mount_options->server_path + 1;
			dout("mount opening path %s\n", path);
		}

		ceph_fs_debugfs_init(fsc);

		root = open_root_dentry(fsc, path, started);
		if (IS_ERR(root)) {
			err = PTR_ERR(root);
			goto out;
		}
		fsc->sb->s_root = dget(root);
	} else {
		root = dget(fsc->sb->s_root);
	}

	fsc->mount_state = CEPH_MOUNT_MOUNTED;
	dout("mount success\n");
	mutex_unlock(&fsc->client->mount_mutex);
	return root;

out:
	mutex_unlock(&fsc->client->mount_mutex);
	return ERR_PTR(err);
}