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
struct path {int /*<<< orphan*/ * mnt; int /*<<< orphan*/ * dentry; } ;
struct fs_parameter {int type; int /*<<< orphan*/  key; int /*<<< orphan*/  dirfd; struct filename* name; int /*<<< orphan*/  string; } ;
struct fs_context {int dummy; } ;
struct filename {int /*<<< orphan*/  name; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int ENOTBLK ; 
 int /*<<< orphan*/  IS_ERR (struct filename*) ; 
 unsigned int LOOKUP_EMPTY ; 
 int PTR_ERR (struct filename*) ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 TYPE_1__* d_backing_inode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errorf (struct fs_context*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int filename_lookup (int /*<<< orphan*/ ,struct filename*,unsigned int,struct path*,int /*<<< orphan*/ *) ; 
#define  fs_value_is_filename 130 
#define  fs_value_is_filename_empty 129 
#define  fs_value_is_string 128 
 struct filename* getname_kernel (int /*<<< orphan*/ ) ; 
 int invalf (struct fs_context*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  putname (struct filename*) ; 

int fs_lookup_param(struct fs_context *fc,
		    struct fs_parameter *param,
		    bool want_bdev,
		    struct path *_path)
{
	struct filename *f;
	unsigned int flags = 0;
	bool put_f;
	int ret;

	switch (param->type) {
	case fs_value_is_string:
		f = getname_kernel(param->string);
		if (IS_ERR(f))
			return PTR_ERR(f);
		put_f = true;
		break;
	case fs_value_is_filename_empty:
		flags = LOOKUP_EMPTY;
		/* Fall through */
	case fs_value_is_filename:
		f = param->name;
		put_f = false;
		break;
	default:
		return invalf(fc, "%s: not usable as path", param->key);
	}

	f->refcnt++; /* filename_lookup() drops our ref. */
	ret = filename_lookup(param->dirfd, f, flags, _path, NULL);
	if (ret < 0) {
		errorf(fc, "%s: Lookup failure for '%s'", param->key, f->name);
		goto out;
	}

	if (want_bdev &&
	    !S_ISBLK(d_backing_inode(_path->dentry)->i_mode)) {
		path_put(_path);
		_path->dentry = NULL;
		_path->mnt = NULL;
		errorf(fc, "%s: Non-blockdev passed as '%s'",
		       param->key, f->name);
		ret = -ENOTBLK;
	}

out:
	if (put_f)
		putname(f);
	return ret;
}