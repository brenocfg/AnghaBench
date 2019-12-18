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
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  psignal (int,char*) ; 
 int /*<<< orphan*/  raise (int) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

void sighandler_dump_stack(int sig)
{
	psignal(sig, "perf");
	dump_stack();
	signal(sig, SIG_DFL);
	raise(sig);
}