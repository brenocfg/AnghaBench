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
struct afs_addr_list {int /*<<< orphan*/  index; } ;
struct afs_addr_cursor {int begun; int error; struct afs_addr_list* alist; int /*<<< orphan*/ * addr; int /*<<< orphan*/  index; int /*<<< orphan*/  start; scalar_t__ responded; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_put_addrlist (struct afs_addr_list*) ; 

int afs_end_cursor(struct afs_addr_cursor *ac)
{
	struct afs_addr_list *alist;

	alist = ac->alist;
	if (alist) {
		if (ac->responded && ac->index != ac->start)
			WRITE_ONCE(alist->index, ac->index);
		afs_put_addrlist(alist);
	}

	ac->addr = NULL;
	ac->alist = NULL;
	ac->begun = false;
	return ac->error;
}