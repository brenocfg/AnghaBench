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
typedef  int /*<<< orphan*/  MSG ;

/* Variables and functions */
 int /*<<< orphan*/  PM_NOREMOVE ; 
 scalar_t__ pPeekMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_message () ; 
 int /*<<< orphan*/  s_busy_processing ; 
 int /*<<< orphan*/  vim_is_input_buf_full () ; 

void
gui_mch_update(void)
{
    MSG	    msg;

    if (!s_busy_processing)
	while (pPeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)
						  && !vim_is_input_buf_full())
	    process_message();
}