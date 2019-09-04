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
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_11__ {int argvar; int numargs; TYPE_3__* args; } ;
struct TYPE_8__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_9__ {TYPE_1__ h; } ;
struct TYPE_12__ {TYPE_4__ out; TYPE_2__ in; } ;
struct TYPE_10__ {char* value; scalar_t__ size; } ;

/* Variables and functions */
 size_t ECHILD ; 
 size_t ENOMEM ; 
 char const* ERR_PTR (size_t) ; 
 int /*<<< orphan*/  FUSE_ARGS (TYPE_5__) ; 
 int /*<<< orphan*/  FUSE_READLINK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 TYPE_5__ args ; 
 int /*<<< orphan*/  fuse_invalidate_atime (struct inode*) ; 
 size_t fuse_simple_request (struct fuse_conn*,TYPE_5__*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kfree_link ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const char *fuse_get_link(struct dentry *dentry,
				 struct inode *inode,
				 struct delayed_call *done)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	FUSE_ARGS(args);
	char *link;
	ssize_t ret;

	if (!dentry)
		return ERR_PTR(-ECHILD);

	link = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!link)
		return ERR_PTR(-ENOMEM);

	args.in.h.opcode = FUSE_READLINK;
	args.in.h.nodeid = get_node_id(inode);
	args.out.argvar = 1;
	args.out.numargs = 1;
	args.out.args[0].size = PAGE_SIZE - 1;
	args.out.args[0].value = link;
	ret = fuse_simple_request(fc, &args);
	if (ret < 0) {
		kfree(link);
		link = ERR_PTR(ret);
	} else {
		link[ret] = '\0';
		set_delayed_call(done, kfree_link, link);
	}
	fuse_invalidate_atime(inode);
	return link;
}