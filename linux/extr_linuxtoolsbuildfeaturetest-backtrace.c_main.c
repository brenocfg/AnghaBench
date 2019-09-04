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
 size_t backtrace (void**,int) ; 
 int /*<<< orphan*/  backtrace_symbols_fd (void**,size_t,int) ; 

int main(void)
{
	void *backtrace_fns[10];
	size_t entries;

	entries = backtrace(backtrace_fns, 10);
	backtrace_symbols_fd(backtrace_fns, entries, 1);

	return 0;
}