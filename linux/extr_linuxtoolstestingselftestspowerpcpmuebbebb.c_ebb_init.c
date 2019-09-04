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
struct TYPE_2__ {int /*<<< orphan*/  trace; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  clear_ebb_stats () ; 
 TYPE_1__ ebb_state ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  term_action ; 
 int /*<<< orphan*/  trace_buffer_allocate (int) ; 

__attribute__((used)) static void __attribute__((constructor)) ebb_init(void)
{
	clear_ebb_stats();

	if (sigaction(SIGTERM, &term_action, NULL))
		perror("sigaction");

	ebb_state.trace = trace_buffer_allocate(1 * 1024 * 1024);
}