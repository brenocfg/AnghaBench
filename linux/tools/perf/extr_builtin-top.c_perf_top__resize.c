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
struct perf_top {int /*<<< orphan*/  winsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_term_dimensions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_top__update_print_entries (struct perf_top*) ; 

__attribute__((used)) static void perf_top__resize(struct perf_top *top)
{
	get_term_dimensions(&top->winsize);
	perf_top__update_print_entries(top);
}