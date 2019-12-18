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
struct kernel_siginfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int force_sig_info_to_task (struct kernel_siginfo*,int /*<<< orphan*/ ) ; 

int force_sig_info(struct kernel_siginfo *info)
{
	return force_sig_info_to_task(info, current);
}