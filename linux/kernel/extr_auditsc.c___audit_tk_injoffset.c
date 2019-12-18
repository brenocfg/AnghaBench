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
struct timespec64 {int /*<<< orphan*/  tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_TIME_INJOFFSET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,long long,int /*<<< orphan*/ ) ; 

void __audit_tk_injoffset(struct timespec64 offset)
{
	audit_log(audit_context(), GFP_KERNEL, AUDIT_TIME_INJOFFSET,
		  "sec=%lli nsec=%li",
		  (long long)offset.tv_sec, offset.tv_nsec);
}