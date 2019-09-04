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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* args; } ;
struct fuse_req {int num_pages; int /*<<< orphan*/ * pages; TYPE_2__ out; } ;
struct fuse_conn {scalar_t__ writeback_cache; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_3__ {size_t size; } ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  fuse_read_update_size (struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 scalar_t__ page_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero_user_segment (int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static void fuse_short_read(struct fuse_req *req, struct inode *inode,
			    u64 attr_ver)
{
	size_t num_read = req->out.args[0].size;
	struct fuse_conn *fc = get_fuse_conn(inode);

	if (fc->writeback_cache) {
		/*
		 * A hole in a file. Some data after the hole are in page cache,
		 * but have not reached the client fs yet. So, the hole is not
		 * present there.
		 */
		int i;
		int start_idx = num_read >> PAGE_SHIFT;
		size_t off = num_read & (PAGE_SIZE - 1);

		for (i = start_idx; i < req->num_pages; i++) {
			zero_user_segment(req->pages[i], off, PAGE_SIZE);
			off = 0;
		}
	} else {
		loff_t pos = page_offset(req->pages[0]) + num_read;
		fuse_read_update_size(inode, pos, attr_ver);
	}
}