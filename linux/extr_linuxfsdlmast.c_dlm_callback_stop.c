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
struct dlm_ls {scalar_t__ ls_callback_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 

void dlm_callback_stop(struct dlm_ls *ls)
{
	if (ls->ls_callback_wq)
		destroy_workqueue(ls->ls_callback_wq);
}