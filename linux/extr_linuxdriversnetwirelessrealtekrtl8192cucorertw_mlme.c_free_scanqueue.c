#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct mlme_priv {int /*<<< orphan*/  num_of_scanned; TYPE_1__ scanned_queue; TYPE_1__ free_bss_pool; } ;
typedef  TYPE_1__ _queue ;
typedef  int /*<<< orphan*/  _list ;
typedef  int /*<<< orphan*/  _irqL ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/ * get_list_head (TYPE_1__*) ; 
 int /*<<< orphan*/ * get_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_scanqueue(struct	mlme_priv *pmlmepriv)
{
	_irqL irqL, irqL0;
	_queue *free_queue = &pmlmepriv->free_bss_pool;
	_queue *scan_queue = &pmlmepriv->scanned_queue;
	_list	*plist, *phead, *ptemp;
	
_func_enter_;		
	
	RT_TRACE(_module_rtl871x_mlme_c_, _drv_notice_, ("+free_scanqueue\n"));
	_enter_critical_bh(&scan_queue->lock, &irqL0);
	_enter_critical_bh(&free_queue->lock, &irqL);

	phead = get_list_head(scan_queue);
	plist = get_next(phead);

	while (plist != phead)
       {
		ptemp = get_next(plist);
		rtw_list_delete(plist);
		rtw_list_insert_tail(plist, &free_queue->queue);
		plist =ptemp;
		pmlmepriv->num_of_scanned --;
        }
	
	_exit_critical_bh(&free_queue->lock, &irqL);
	_exit_critical_bh(&scan_queue->lock, &irqL0);
	
_func_exit_;
}