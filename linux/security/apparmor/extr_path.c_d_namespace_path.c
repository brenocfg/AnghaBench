#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_3__* dentry; TYPE_2__* mnt; } ;
struct TYPE_11__ {int /*<<< orphan*/  fs; } ;
struct TYPE_10__ {TYPE_1__* d_sb; } ;
struct TYPE_9__ {int mnt_flags; } ;
struct TYPE_8__ {scalar_t__ s_magic; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (char*) ; 
 int MNT_INTERNAL ; 
 int PATH_CHROOT_REL ; 
 int PATH_DELEGATE_DELETED ; 
 int PATH_IS_DIR ; 
 int PATH_MEDIATE_DELETED ; 
 scalar_t__ PROC_SUPER_MAGIC ; 
 int PTR_ERR (char*) ; 
 char* __d_path (struct path const*,struct path*,char*,int) ; 
 int aa_g_path_max ; 
 TYPE_7__* current ; 
 char* d_absolute_path (struct path const*,char*,int) ; 
 scalar_t__ d_is_positive (TYPE_3__*) ; 
 scalar_t__ d_unlinked (TYPE_3__*) ; 
 char* dentry_path (TYPE_3__*,char*,int) ; 
 char* dentry_path_raw (TYPE_3__*,char*,int) ; 
 int disconnect (struct path const*,char*,char**,int,char const*) ; 
 int /*<<< orphan*/  get_fs_root (int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  our_mnt (TYPE_2__*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int prepend (char**,int,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int d_namespace_path(const struct path *path, char *buf, char **name,
			    int flags, const char *disconnected)
{
	char *res;
	int error = 0;
	int connected = 1;
	int isdir = (flags & PATH_IS_DIR) ? 1 : 0;
	int buflen = aa_g_path_max - isdir;

	if (path->mnt->mnt_flags & MNT_INTERNAL) {
		/* it's not mounted anywhere */
		res = dentry_path(path->dentry, buf, buflen);
		*name = res;
		if (IS_ERR(res)) {
			*name = buf;
			return PTR_ERR(res);
		}
		if (path->dentry->d_sb->s_magic == PROC_SUPER_MAGIC &&
		    strncmp(*name, "/sys/", 5) == 0) {
			/* TODO: convert over to using a per namespace
			 * control instead of hard coded /proc
			 */
			error = prepend(name, *name - buf, "/proc", 5);
			goto out;
		} else
			error = disconnect(path, buf, name, flags,
					   disconnected);
		goto out;
	}

	/* resolve paths relative to chroot?*/
	if (flags & PATH_CHROOT_REL) {
		struct path root;
		get_fs_root(current->fs, &root);
		res = __d_path(path, &root, buf, buflen);
		path_put(&root);
	} else {
		res = d_absolute_path(path, buf, buflen);
		if (!our_mnt(path->mnt))
			connected = 0;
	}

	/* handle error conditions - and still allow a partial path to
	 * be returned.
	 */
	if (!res || IS_ERR(res)) {
		if (PTR_ERR(res) == -ENAMETOOLONG) {
			error = -ENAMETOOLONG;
			*name = buf;
			goto out;
		}
		connected = 0;
		res = dentry_path_raw(path->dentry, buf, buflen);
		if (IS_ERR(res)) {
			error = PTR_ERR(res);
			*name = buf;
			goto out;
		};
	} else if (!our_mnt(path->mnt))
		connected = 0;

	*name = res;

	if (!connected)
		error = disconnect(path, buf, name, flags, disconnected);

	/* Handle two cases:
	 * 1. A deleted dentry && profile is not allowing mediation of deleted
	 * 2. On some filesystems, newly allocated dentries appear to the
	 *    security_path hooks as a deleted dentry except without an inode
	 *    allocated.
	 */
	if (d_unlinked(path->dentry) && d_is_positive(path->dentry) &&
	    !(flags & (PATH_MEDIATE_DELETED | PATH_DELEGATE_DELETED))) {
			error = -ENOENT;
			goto out;
	}

out:
	/*
	 * Append "/" to the pathname.  The root directory is a special
	 * case; it already ends in slash.
	 */
	if (!error && isdir && ((*name)[1] != '\0' || (*name)[0] != '/'))
		strcpy(&buf[aa_g_path_max - 2], "/");

	return error;
}