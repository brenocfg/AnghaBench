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
struct afs_addr_cursor {size_t start; size_t index; int begun; int responded; TYPE_1__* alist; int /*<<< orphan*/ * addr; int /*<<< orphan*/  error; } ;
struct TYPE_2__ {size_t nr_addrs; int /*<<< orphan*/ * addrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDESTADDRREQ ; 
 int /*<<< orphan*/  _enter (char*,size_t,short) ; 

bool afs_iterate_addresses(struct afs_addr_cursor *ac)
{
	_enter("%hu+%hd", ac->start, (short)ac->index);

	if (!ac->alist)
		return false;

	if (ac->begun) {
		ac->index++;
		if (ac->index == ac->alist->nr_addrs)
			ac->index = 0;

		if (ac->index == ac->start) {
			ac->error = -EDESTADDRREQ;
			return false;
		}
	}

	ac->begun = true;
	ac->responded = false;
	ac->addr = &ac->alist->addrs[ac->index];
	return true;
}