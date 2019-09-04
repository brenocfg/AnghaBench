#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_9__ {int len; char const* name; } ;
struct dentry {TYPE_2__ d_name; } ;
struct TYPE_8__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_11__ {int numargs; TYPE_3__* args; TYPE_1__ h; } ;
struct TYPE_12__ {TYPE_4__ in; } ;
struct TYPE_10__ {int size; char const* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_ARGS (TYPE_5__) ; 
 int /*<<< orphan*/  FUSE_SYMLINK ; 
 int /*<<< orphan*/  S_IFLNK ; 
 TYPE_5__ args ; 
 int create_new_entry (struct fuse_conn*,TYPE_5__*,struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int fuse_symlink(struct inode *dir, struct dentry *entry,
			const char *link)
{
	struct fuse_conn *fc = get_fuse_conn(dir);
	unsigned len = strlen(link) + 1;
	FUSE_ARGS(args);

	args.in.h.opcode = FUSE_SYMLINK;
	args.in.numargs = 2;
	args.in.args[0].size = entry->d_name.len + 1;
	args.in.args[0].value = entry->d_name.name;
	args.in.args[1].size = len;
	args.in.args[1].value = link;
	return create_new_entry(fc, &args, dir, entry, S_IFLNK);
}