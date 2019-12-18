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
struct page {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int ceph_do_readpage (struct file*,struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int ceph_readpage(struct file *filp, struct page *page)
{
	int r = ceph_do_readpage(filp, page);
	if (r != -EINPROGRESS)
		unlock_page(page);
	else
		r = 0;
	return r;
}