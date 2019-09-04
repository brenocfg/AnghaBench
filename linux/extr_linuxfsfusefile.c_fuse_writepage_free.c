#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fuse_req {int num_pages; scalar_t__ ff; int /*<<< orphan*/ * pages; } ;
struct fuse_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_file_put (scalar_t__,int,int) ; 

__attribute__((used)) static void fuse_writepage_free(struct fuse_conn *fc, struct fuse_req *req)
{
	int i;

	for (i = 0; i < req->num_pages; i++)
		__free_page(req->pages[i]);

	if (req->ff)
		fuse_file_put(req->ff, false, false);
}