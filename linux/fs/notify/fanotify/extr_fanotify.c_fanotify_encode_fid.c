#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * val; } ;
struct fanotify_fid {int /*<<< orphan*/ * ext_fh; TYPE_1__ fsid; } ;
struct fanotify_event {int fh_len; struct fanotify_fid fid; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  TYPE_1__ __kernel_fsid_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int FANOTIFY_INLINE_FH_LEN ; 
 int FILEID_INVALID ; 
 int exportfs_encode_inode_fh (struct inode*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fanotify_fid_fh (struct fanotify_fid*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int fanotify_encode_fid(struct fanotify_event *event,
			       struct inode *inode, gfp_t gfp,
			       __kernel_fsid_t *fsid)
{
	struct fanotify_fid *fid = &event->fid;
	int dwords, bytes = 0;
	int err, type;

	fid->ext_fh = NULL;
	dwords = 0;
	err = -ENOENT;
	type = exportfs_encode_inode_fh(inode, NULL, &dwords, NULL);
	if (!dwords)
		goto out_err;

	bytes = dwords << 2;
	if (bytes > FANOTIFY_INLINE_FH_LEN) {
		/* Treat failure to allocate fh as failure to allocate event */
		err = -ENOMEM;
		fid->ext_fh = kmalloc(bytes, gfp);
		if (!fid->ext_fh)
			goto out_err;
	}

	type = exportfs_encode_inode_fh(inode, fanotify_fid_fh(fid, bytes),
					&dwords, NULL);
	err = -EINVAL;
	if (!type || type == FILEID_INVALID || bytes != dwords << 2)
		goto out_err;

	fid->fsid = *fsid;
	event->fh_len = bytes;

	return type;

out_err:
	pr_warn_ratelimited("fanotify: failed to encode fid (fsid=%x.%x, "
			    "type=%d, bytes=%d, err=%i)\n",
			    fsid->val[0], fsid->val[1], type, bytes, err);
	kfree(fid->ext_fh);
	fid->ext_fh = NULL;
	event->fh_len = 0;

	return FILEID_INVALID;
}