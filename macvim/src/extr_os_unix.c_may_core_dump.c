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
 scalar_t__ deadly_signal ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  signal (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
may_core_dump()
{
    if (deadly_signal != 0)
    {
	signal(deadly_signal, SIG_DFL);
	kill(getpid(), deadly_signal);	/* Die using the signal we caught */
    }
}