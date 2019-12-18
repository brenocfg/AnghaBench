#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct path {int /*<<< orphan*/  dentry; } ;
struct cred {int dummy; } ;
struct cachefiles_cache {int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHEFILES_DEAD ; 
 int /*<<< orphan*/  CACHEFILES_READY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  cachefiles_begin_secure (struct cachefiles_cache*,struct cred const**) ; 
 int cachefiles_check_in_use (struct cachefiles_cache*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cachefiles_end_secure (struct cachefiles_cache*,struct cred const*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  d_can_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_fs_pwd (int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cachefiles_daemon_inuse(struct cachefiles_cache *cache, char *args)
{
	struct path path;
	const struct cred *saved_cred;
	int ret;

	//_enter(",%s", args);

	if (strchr(args, '/'))
		goto inval;

	if (!test_bit(CACHEFILES_READY, &cache->flags)) {
		pr_err("inuse applied to unready cache\n");
		return -EIO;
	}

	if (test_bit(CACHEFILES_DEAD, &cache->flags)) {
		pr_err("inuse applied to dead cache\n");
		return -EIO;
	}

	/* extract the directory dentry from the cwd */
	get_fs_pwd(current->fs, &path);

	if (!d_can_lookup(path.dentry))
		goto notdir;

	cachefiles_begin_secure(cache, &saved_cred);
	ret = cachefiles_check_in_use(cache, path.dentry, args);
	cachefiles_end_secure(cache, saved_cred);

	path_put(&path);
	//_leave(" = %d", ret);
	return ret;

notdir:
	path_put(&path);
	pr_err("inuse command requires dirfd to be a directory\n");
	return -ENOTDIR;

inval:
	pr_err("inuse command requires dirfd and filename\n");
	return -EINVAL;
}