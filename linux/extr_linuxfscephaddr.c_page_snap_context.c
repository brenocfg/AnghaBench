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
struct page {scalar_t__ private; } ;
typedef  void ceph_snap_context ;

/* Variables and functions */
 scalar_t__ PagePrivate (struct page*) ; 

__attribute__((used)) static inline struct ceph_snap_context *page_snap_context(struct page *page)
{
	if (PagePrivate(page))
		return (void *)page->private;
	return NULL;
}