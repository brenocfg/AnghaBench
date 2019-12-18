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
struct afs_addr_list {scalar_t__ preferred; } ;
struct afs_addr_cursor {scalar_t__ index; int error; struct afs_addr_list* alist; int /*<<< orphan*/  tried; scalar_t__ responded; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  afs_put_addrlist (struct afs_addr_list*) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ *) ; 

int afs_end_cursor(struct afs_addr_cursor *ac)
{
	struct afs_addr_list *alist;

	alist = ac->alist;
	if (alist) {
		if (ac->responded &&
		    ac->index != alist->preferred &&
		    test_bit(ac->alist->preferred, &ac->tried))
			WRITE_ONCE(alist->preferred, ac->index);
		afs_put_addrlist(alist);
		ac->alist = NULL;
	}

	return ac->error;
}