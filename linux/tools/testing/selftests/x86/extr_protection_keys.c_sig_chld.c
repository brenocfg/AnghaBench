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
 int dprint_in_signal ; 
 int /*<<< orphan*/  dprintf2 (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  getpid () ; 

void sig_chld(int x)
{
	dprint_in_signal = 1;
	dprintf2("[%d] SIGCHLD: %d\n", getpid(), x);
	dprint_in_signal = 0;
}