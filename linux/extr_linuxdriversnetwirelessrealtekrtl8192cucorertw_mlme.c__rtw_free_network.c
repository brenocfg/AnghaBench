#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct wlan_network {scalar_t__ fixed; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct mlme_priv {int /*<<< orphan*/  num_of_scanned; TYPE_1__ free_bss_pool; } ;
typedef  TYPE_1__ _queue ;
typedef  int /*<<< orphan*/  _irqL ;

/* Variables and functions */
 int SCANQUEUE_LIFETIME ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int rtw_get_current_time () ; 
 int /*<<< orphan*/  rtw_list_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void _rtw_free_network(struct	mlme_priv *pmlmepriv ,struct wlan_network *pnetwork, u8 isfreeall)
{
	u32 curr_time, delta_time;
	u32 lifetime = SCANQUEUE_LIFETIME;
	_irqL irqL;	
	_queue *free_queue = &(pmlmepriv->free_bss_pool);
	
_func_enter_;		

	if (pnetwork == NULL)
		goto exit;

	if (pnetwork->fixed == _TRUE)
		goto exit;

	curr_time = rtw_get_current_time();	

	if ( (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE)==_TRUE ) || 
		(check_fwstate(pmlmepriv, WIFI_ADHOC_STATE)==_TRUE ) )
		lifetime = 1;

	if(!isfreeall)
	{
#ifdef PLATFORM_WINDOWS

		delta_time = (curr_time -pnetwork->last_scanned)/10;

		if(delta_time  < lifetime*1000000)// unit:usec
		{
			goto exit;
		}

#endif

#ifdef PLATFORM_LINUX

		delta_time = (curr_time -pnetwork->last_scanned)/HZ;	

		if(delta_time < lifetime)// unit:sec
		{		
			goto exit;
		}

#endif

#ifdef PLATFORM_FREEBSD
        //i think needs to check again
		delta_time = (curr_time -pnetwork->last_scanned)/hz;	

		if(delta_time < lifetime)// unit:sec
		{		
			goto exit;
		}

#endif
	}

	_enter_critical_bh(&free_queue->lock, &irqL);
	
	rtw_list_delete(&(pnetwork->list));

	rtw_list_insert_tail(&(pnetwork->list),&(free_queue->queue));
		
	pmlmepriv->num_of_scanned --;
	

	//DBG_871X("_rtw_free_network:SSID=%s\n", pnetwork->network.Ssid.Ssid);
	
	_exit_critical_bh(&free_queue->lock, &irqL);
	
exit:		
	
_func_exit_;			

}