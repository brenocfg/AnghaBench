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
 int /*<<< orphan*/  SKIP_IF (int) ; 
 int /*<<< orphan*/  perf_breakpoint_supported () ; 
 int runtest () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perf_hwbreak(void)
{
	srand ( time(NULL) );

	SKIP_IF(!perf_breakpoint_supported());

	return runtest();
}