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
 int SIGBREAKF_CTRL_C ; 
 int SIGBREAKF_CTRL_D ; 
 int SIGBREAKF_CTRL_E ; 
 int SIGBREAKF_CTRL_F ; 
 int SetSignal (long,long) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  got_int ; 

void
mch_breakcheck()
{
   if (SetSignal(0L, (long)(SIGBREAKF_CTRL_C|SIGBREAKF_CTRL_D|SIGBREAKF_CTRL_E|SIGBREAKF_CTRL_F)) & SIGBREAKF_CTRL_C)
	got_int = TRUE;
}