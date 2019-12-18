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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int PF_KTHREAD ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  current_cred () ; 
 int smack_privileged_cred (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

bool smack_privileged(int cap)
{
	/*
	 * All kernel tasks are privileged
	 */
	if (unlikely(current->flags & PF_KTHREAD))
		return true;

	return smack_privileged_cred(cap, current_cred());
}