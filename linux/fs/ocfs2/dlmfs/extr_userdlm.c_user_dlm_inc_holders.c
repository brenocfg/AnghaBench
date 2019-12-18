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
struct user_lock_res {int /*<<< orphan*/  l_ro_holders; int /*<<< orphan*/  l_ex_holders; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DLM_LOCK_EX 129 
#define  DLM_LOCK_PR 128 

__attribute__((used)) static inline void user_dlm_inc_holders(struct user_lock_res *lockres,
					int level)
{
	switch(level) {
	case DLM_LOCK_EX:
		lockres->l_ex_holders++;
		break;
	case DLM_LOCK_PR:
		lockres->l_ro_holders++;
		break;
	default:
		BUG();
	}
}