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
 scalar_t__ SM_POST_INIT ; 
 scalar_t__ SM_PRE_INIT ; 
 int /*<<< orphan*/  post_init_signal_catch () ; 
 int /*<<< orphan*/  pre_init_signal_catch () ; 
 scalar_t__ signal_mode ; 

void
restore_signal_state(void)
{
#ifdef HAVE_SIGNAL_H
    if (signal_mode == SM_PRE_INIT)
    {
        pre_init_signal_catch();
    }
    else if (signal_mode == SM_POST_INIT)
    {
        post_init_signal_catch();
    }
#endif
}