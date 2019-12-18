#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct fuse_page_desc {int length; } ;
struct fuse_conn {int dummy; } ;
struct TYPE_4__ {int out_pages; int out_argvar; int page_zeroing; int out_numargs; TYPE_1__* out_args; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct fuse_args_pages {int num_pages; TYPE_2__ args; struct fuse_page_desc* descs; struct page** pages; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int size; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FUSE_READLINK ; 
 int PAGE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  fuse_invalidate_atime (struct inode*) ; 
 int fuse_simple_request (struct fuse_conn*,TYPE_2__*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 char* page_address (struct page*) ; 

__attribute__((used)) static int fuse_readlink_page(struct inode *inode, struct page *page)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_page_desc desc = { .length = PAGE_SIZE - 1 };
	struct fuse_args_pages ap = {
		.num_pages = 1,
		.pages = &page,
		.descs = &desc,
	};
	char *link;
	ssize_t res;

	ap.args.opcode = FUSE_READLINK;
	ap.args.nodeid = get_node_id(inode);
	ap.args.out_pages = true;
	ap.args.out_argvar = true;
	ap.args.page_zeroing = true;
	ap.args.out_numargs = 1;
	ap.args.out_args[0].size = desc.length;
	res = fuse_simple_request(fc, &ap.args);

	fuse_invalidate_atime(inode);

	if (res < 0)
		return res;

	if (WARN_ON(res >= PAGE_SIZE))
		return -EIO;

	link = page_address(page);
	link[res] = '\0';

	return 0;
}