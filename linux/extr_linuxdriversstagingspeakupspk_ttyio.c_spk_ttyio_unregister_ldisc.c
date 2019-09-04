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
 int /*<<< orphan*/  N_SPEAKUP ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ tty_unregister_ldisc (int /*<<< orphan*/ ) ; 

void spk_ttyio_unregister_ldisc(void)
{
	if (tty_unregister_ldisc(N_SPEAKUP))
		pr_warn("speakup: Couldn't unregister ldisc\n");
}