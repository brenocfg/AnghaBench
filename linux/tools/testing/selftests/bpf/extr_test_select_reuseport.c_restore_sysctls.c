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

/* Variables and functions */
 int /*<<< orphan*/  TCP_FO_SYSCTL ; 
 int /*<<< orphan*/  TCP_SYNCOOKIE_SYSCTL ; 
 int /*<<< orphan*/  saved_tcp_fo ; 
 int /*<<< orphan*/  saved_tcp_syncookie ; 
 int /*<<< orphan*/  write_int_sysctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void restore_sysctls(void)
{
	write_int_sysctl(TCP_FO_SYSCTL, saved_tcp_fo);
	write_int_sysctl(TCP_SYNCOOKIE_SYSCTL, saved_tcp_syncookie);
}