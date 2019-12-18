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
 int /*<<< orphan*/  __T_OK ; 
 int /*<<< orphan*/  __T_START ; 
 int /*<<< orphan*/  libperf_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libperf_print ; 
 int /*<<< orphan*/  test_stat_cpu () ; 
 int /*<<< orphan*/  test_stat_thread () ; 
 int /*<<< orphan*/  test_stat_thread_enable () ; 

int main(int argc, char **argv)
{
	__T_START;

	libperf_init(libperf_print);

	test_stat_cpu();
	test_stat_thread();
	test_stat_thread_enable();

	__T_OK;
	return 0;
}