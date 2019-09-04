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
struct fuse_req {TYPE_1__* page_descs; } ;
struct TYPE_2__ {scalar_t__ offset; scalar_t__ length; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static inline void fuse_page_descs_length_init(struct fuse_req *req,
		unsigned index, unsigned nr_pages)
{
	int i;

	for (i = index; i < index + nr_pages; i++)
		req->page_descs[i].length = PAGE_SIZE -
			req->page_descs[i].offset;
}