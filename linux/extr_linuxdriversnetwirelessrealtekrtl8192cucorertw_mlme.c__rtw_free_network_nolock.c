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
struct wlan_network {scalar_t__ fixed; int /*<<< orphan*/  list; } ;
struct mlme_priv {int /*<<< orphan*/  num_of_scanned; int /*<<< orphan*/  free_bss_pool; } ;
typedef  int /*<<< orphan*/  _queue ;

/* Variables and functions */
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  get_list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void _rtw_free_network_nolock(struct	mlme_priv *pmlmepriv, struct wlan_network *pnetwork)
{

	_queue *free_queue = &(pmlmepriv->free_bss_pool);

_func_enter_;		

	if (pnetwork == NULL)
		goto exit;

	if (pnetwork->fixed == _TRUE)
		goto exit;

	//_enter_critical(&free_queue->lock, &irqL);
	
	rtw_list_delete(&(pnetwork->list));

	rtw_list_insert_tail(&(pnetwork->list), get_list_head(free_queue));
		
	pmlmepriv->num_of_scanned --;
	
	//_exit_critical(&free_queue->lock, &irqL);
	
exit:		

_func_exit_;			

}