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
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ emsg_silent ; 
 int /*<<< orphan*/  flush_buffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vim_beep () ; 

void
beep_flush()
{
    if (emsg_silent == 0)
    {
	flush_buffers(FALSE);
	vim_beep();
    }
}