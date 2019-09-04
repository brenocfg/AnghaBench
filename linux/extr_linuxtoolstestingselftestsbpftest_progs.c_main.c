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
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int error_cnt ; 
 int /*<<< orphan*/  is_jit_enabled () ; 
 int /*<<< orphan*/  jit_enabled ; 
 int pass_cnt ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  test_bpf_obj_id () ; 
 int /*<<< orphan*/  test_get_stack_raw_tp () ; 
 int /*<<< orphan*/  test_l4lb_all () ; 
 int /*<<< orphan*/  test_obj_name () ; 
 int /*<<< orphan*/  test_pkt_access () ; 
 int /*<<< orphan*/  test_pkt_md_access () ; 
 int /*<<< orphan*/  test_stacktrace_build_id () ; 
 int /*<<< orphan*/  test_stacktrace_build_id_nmi () ; 
 int /*<<< orphan*/  test_stacktrace_map () ; 
 int /*<<< orphan*/  test_stacktrace_map_raw_tp () ; 
 int /*<<< orphan*/  test_task_fd_query_rawtp () ; 
 int /*<<< orphan*/  test_task_fd_query_tp () ; 
 int /*<<< orphan*/  test_tcp_estats () ; 
 int /*<<< orphan*/  test_tp_attach_query () ; 
 int /*<<< orphan*/  test_xdp () ; 
 int /*<<< orphan*/  test_xdp_adjust_tail () ; 
 int /*<<< orphan*/  test_xdp_noinline () ; 

int main(void)
{
	jit_enabled = is_jit_enabled();

	test_pkt_access();
	test_xdp();
	test_xdp_adjust_tail();
	test_l4lb_all();
	test_xdp_noinline();
	test_tcp_estats();
	test_bpf_obj_id();
	test_pkt_md_access();
	test_obj_name();
	test_tp_attach_query();
	test_stacktrace_map();
	test_stacktrace_build_id();
	test_stacktrace_build_id_nmi();
	test_stacktrace_map_raw_tp();
	test_get_stack_raw_tp();
	test_task_fd_query_rawtp();
	test_task_fd_query_tp();

	printf("Summary: %d PASSED, %d FAILED\n", pass_cnt, error_cnt);
	return error_cnt ? EXIT_FAILURE : EXIT_SUCCESS;
}