#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct fuse_rename2_in {unsigned int flags; void* newdir; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_7__ {int len; struct fuse_rename2_in* name; } ;
struct dentry {TYPE_2__ d_name; } ;
struct TYPE_8__ {int opcode; int in_numargs; TYPE_1__* in_args; void* nodeid; } ;
struct TYPE_6__ {size_t size; struct fuse_rename2_in* value; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_3__) ; 
 unsigned int RENAME_EXCHANGE ; 
 TYPE_3__ args ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  fuse_dir_changed (struct inode*) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_invalidate_entry (struct dentry*) ; 
 int /*<<< orphan*/  fuse_invalidate_entry_cache (struct dentry*) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_3__*) ; 
 int /*<<< orphan*/  fuse_update_ctime (int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 void* get_node_id (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_rename2_in*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int fuse_rename_common(struct inode *olddir, struct dentry *oldent,
			      struct inode *newdir, struct dentry *newent,
			      unsigned int flags, int opcode, size_t argsize)
{
	int err;
	struct fuse_rename2_in inarg;
	struct fuse_conn *fc = get_fuse_conn(olddir);
	FUSE_ARGS(args);

	memset(&inarg, 0, argsize);
	inarg.newdir = get_node_id(newdir);
	inarg.flags = flags;
	args.opcode = opcode;
	args.nodeid = get_node_id(olddir);
	args.in_numargs = 3;
	args.in_args[0].size = argsize;
	args.in_args[0].value = &inarg;
	args.in_args[1].size = oldent->d_name.len + 1;
	args.in_args[1].value = oldent->d_name.name;
	args.in_args[2].size = newent->d_name.len + 1;
	args.in_args[2].value = newent->d_name.name;
	err = fuse_simple_request(fc, &args);
	if (!err) {
		/* ctime changes */
		fuse_invalidate_attr(d_inode(oldent));
		fuse_update_ctime(d_inode(oldent));

		if (flags & RENAME_EXCHANGE) {
			fuse_invalidate_attr(d_inode(newent));
			fuse_update_ctime(d_inode(newent));
		}

		fuse_dir_changed(olddir);
		if (olddir != newdir)
			fuse_dir_changed(newdir);

		/* newent will end up negative */
		if (!(flags & RENAME_EXCHANGE) && d_really_is_positive(newent)) {
			fuse_invalidate_attr(d_inode(newent));
			fuse_invalidate_entry_cache(newent);
			fuse_update_ctime(d_inode(newent));
		}
	} else if (err == -EINTR) {
		/* If request was interrupted, DEITY only knows if the
		   rename actually took place.  If the invalidation
		   fails (e.g. some process has CWD under the renamed
		   directory), then there can be inconsistency between
		   the dcache and the real filesystem.  Tough luck. */
		fuse_invalidate_entry(oldent);
		if (d_really_is_positive(newent))
			fuse_invalidate_entry(newent);
	}

	return err;
}