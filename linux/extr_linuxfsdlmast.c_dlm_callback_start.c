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
struct dlm_ls {int /*<<< orphan*/  ls_callback_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int WQ_HIGHPRI ; 
 int WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_print (char*) ; 

int dlm_callback_start(struct dlm_ls *ls)
{
	ls->ls_callback_wq = alloc_workqueue("dlm_callback",
					     WQ_HIGHPRI | WQ_MEM_RECLAIM, 0);
	if (!ls->ls_callback_wq) {
		log_print("can't start dlm_callback workqueue");
		return -ENOMEM;
	}
	return 0;
}