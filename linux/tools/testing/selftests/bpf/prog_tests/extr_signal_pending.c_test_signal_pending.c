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
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_FLOW_DISSECTOR ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_SOCKET_FILTER ; 
 int /*<<< orphan*/  test_signal_pending_by_type (int /*<<< orphan*/ ) ; 

void test_signal_pending(enum bpf_prog_type prog_type)
{
	test_signal_pending_by_type(BPF_PROG_TYPE_SOCKET_FILTER);
	test_signal_pending_by_type(BPF_PROG_TYPE_FLOW_DISSECTOR);
}