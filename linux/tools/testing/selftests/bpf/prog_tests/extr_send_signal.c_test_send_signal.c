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
 scalar_t__ test__start_subtest (char*) ; 
 int /*<<< orphan*/  test_send_signal_nmi () ; 
 int /*<<< orphan*/  test_send_signal_perf () ; 
 int /*<<< orphan*/  test_send_signal_tracepoint () ; 

void test_send_signal(void)
{
	if (test__start_subtest("send_signal_tracepoint"))
		test_send_signal_tracepoint();
	if (test__start_subtest("send_signal_perf"))
		test_send_signal_perf();
	if (test__start_subtest("send_signal_nmi"))
		test_send_signal_nmi();
}