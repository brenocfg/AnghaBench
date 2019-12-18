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
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  dump_ebb_hw_state () ; 
 int /*<<< orphan*/  dump_summary_ebb_state () ; 

__attribute__((used)) static void term_handler(int signal)
{
	dump_summary_ebb_state();
	dump_ebb_hw_state();
	abort();
}