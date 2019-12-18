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
typedef  enum lockdown_reason { ____Placeholder_lockdown_reason } lockdown_reason ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int EPERM ; 
 int LOCKDOWN_CONFIDENTIALITY_MAX ; 
 scalar_t__ WARN (int,char*) ; 
 TYPE_1__* current ; 
 int kernel_locked_down ; 
 scalar_t__* lockdown_reasons ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lockdown_is_locked_down(enum lockdown_reason what)
{
	if (WARN(what >= LOCKDOWN_CONFIDENTIALITY_MAX,
		 "Invalid lockdown reason"))
		return -EPERM;

	if (kernel_locked_down >= what) {
		if (lockdown_reasons[what])
			pr_notice("Lockdown: %s: %s is restricted; see man kernel_lockdown.7\n",
				  current->comm, lockdown_reasons[what]);
		return -EPERM;
	}

	return 0;
}