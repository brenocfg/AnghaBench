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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_main_context_iteration (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_main_context_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vim_is_input_buf_full () ; 

void
gui_mch_update(void)
{
    while (g_main_context_pending(NULL) && !vim_is_input_buf_full())
	g_main_context_iteration(NULL, TRUE);
}