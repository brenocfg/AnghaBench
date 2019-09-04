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
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ traffic_busy; } ;
struct mlme_priv {int /*<<< orphan*/  lock; TYPE_1__ sitesurveyctrl; } ;
struct _adapter {int /*<<< orphan*/  hw_init_completed; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int _FW_UNDER_LINKING ; 
 int _FW_UNDER_SURVEY ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int) ; 
 int /*<<< orphan*/  r8712_free_network_queue (struct _adapter*) ; 
 int r8712_sitesurvey_cmd (struct _adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u8 r8712_set_802_11_bssid_list_scan(struct _adapter *padapter)
{
	struct mlme_priv *pmlmepriv = NULL;
	unsigned long irqL;
	u8 ret = true;

	if (!padapter)
		return false;
	pmlmepriv = &padapter->mlmepriv;
	if (!padapter->hw_init_completed)
		return false;
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	if (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY | _FW_UNDER_LINKING) ||
	    pmlmepriv->sitesurveyctrl.traffic_busy) {
		/* Scan or linking is in progress, do nothing. */
		ret = (u8)check_fwstate(pmlmepriv, _FW_UNDER_SURVEY);
	} else {
		r8712_free_network_queue(padapter);
		ret = r8712_sitesurvey_cmd(padapter, NULL);
	}
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	return ret;
}