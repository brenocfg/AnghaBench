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
struct ceph_readdir_cache_control {int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

void ceph_readdir_cache_release(struct ceph_readdir_cache_control *ctl)
{
	if (ctl->page) {
		kunmap(ctl->page);
		put_page(ctl->page);
		ctl->page = NULL;
	}
}