#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  MacAddress; } ;
struct TYPE_4__ {TYPE_1__ network; } ;
struct mlme_priv {int assoc_by_bssid; int /*<<< orphan*/  lock; int /*<<< orphan*/  assoc_bssid; TYPE_2__ cur_network; } ;
struct _adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int WIFI_STATION_STATE ; 
 int _FW_LINKED ; 
 int _FW_UNDER_LINKING ; 
 int _FW_UNDER_SURVEY ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int) ; 
 int check_fwstate (struct mlme_priv*,int) ; 
 int do_join (struct _adapter*) ; 
 scalar_t__ is_broadcast_ether_addr (int*) ; 
 scalar_t__ is_zero_ether_addr (int*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_disassoc_cmd (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_free_assoc_resources (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_ind_disconnect (struct _adapter*) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u8 r8712_set_802_11_bssid(struct _adapter *padapter, u8 *bssid)
{
	unsigned long irqL;
	u8 status = true;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	if (is_zero_ether_addr(bssid) || is_broadcast_ether_addr(bssid)) {
		status = false;
		return status;
	}
	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	if (check_fwstate(pmlmepriv, _FW_UNDER_SURVEY |
	    _FW_UNDER_LINKING)) {
		status = check_fwstate(pmlmepriv, _FW_UNDER_LINKING);
		goto _Abort_Set_BSSID;
	}
	if (check_fwstate(pmlmepriv,
	    _FW_LINKED | WIFI_ADHOC_MASTER_STATE)) {
		if (!memcmp(&pmlmepriv->cur_network.network.MacAddress, bssid,
		    ETH_ALEN)) {
			if (!check_fwstate(pmlmepriv, WIFI_STATION_STATE))
				/* driver is in
				 * WIFI_ADHOC_MASTER_STATE
				 */
				goto _Abort_Set_BSSID;
		} else {
			r8712_disassoc_cmd(padapter);
			if (check_fwstate(pmlmepriv, _FW_LINKED))
				r8712_ind_disconnect(padapter);
			r8712_free_assoc_resources(padapter);
			if ((check_fwstate(pmlmepriv,
			     WIFI_ADHOC_MASTER_STATE))) {
				_clr_fwstate_(pmlmepriv,
					      WIFI_ADHOC_MASTER_STATE);
				set_fwstate(pmlmepriv, WIFI_ADHOC_STATE);
			}
		}
	}
	memcpy(&pmlmepriv->assoc_bssid, bssid, ETH_ALEN);
	pmlmepriv->assoc_by_bssid = true;
	status = do_join(padapter);
	goto done;
_Abort_Set_BSSID:
done:
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	return status;
}