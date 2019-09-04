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
struct dlm_ls {scalar_t__ ls_callback_wq; int /*<<< orphan*/  ls_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSFL_CB_DELAY ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dlm_callback_suspend(struct dlm_ls *ls)
{
	set_bit(LSFL_CB_DELAY, &ls->ls_flags);

	if (ls->ls_callback_wq)
		flush_workqueue(ls->ls_callback_wq);
}