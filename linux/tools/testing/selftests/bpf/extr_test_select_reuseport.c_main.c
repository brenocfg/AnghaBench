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
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup () ; 
 int /*<<< orphan*/  create_maps () ; 
 int /*<<< orphan*/  disable_syncookie () ; 
 int /*<<< orphan*/  enable_fastopen () ; 
 int /*<<< orphan*/  prepare_bpf_obj () ; 
 void* read_int_sysctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_sysctls ; 
 void* saved_tcp_fo ; 
 void* saved_tcp_syncookie ; 
 int /*<<< orphan*/  test_all () ; 

int main(int argc, const char **argv)
{
	create_maps();
	prepare_bpf_obj();
	saved_tcp_fo = read_int_sysctl(TCP_FO_SYSCTL);
	saved_tcp_syncookie = read_int_sysctl(TCP_SYNCOOKIE_SYSCTL);
	enable_fastopen();
	disable_syncookie();
	atexit(restore_sysctls);

	test_all();

	cleanup();
	return 0;
}