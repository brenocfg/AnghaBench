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
struct ndis_802_11_ssid {int dummy; } ;
struct mp_priv {int /*<<< orphan*/  network_macaddr; } ;
struct mlme_priv {int dummy; } ;
struct _adapter {struct mlme_priv mlmepriv; struct mp_priv mppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 int _FAIL ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 unsigned char _SUCCESS ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 unsigned char r8712_setassocsta_cmd (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

int mp_start_joinbss(struct _adapter *padapter, struct ndis_802_11_ssid *pssid)
{
	struct mp_priv *pmppriv = &padapter->mppriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	unsigned char res = _SUCCESS;

	if (!check_fwstate(pmlmepriv, WIFI_MP_STATE))
		return _FAIL;
	if (!check_fwstate(pmlmepriv, _FW_LINKED))
		return _FAIL;
	_clr_fwstate_(pmlmepriv, _FW_LINKED);
	res = r8712_setassocsta_cmd(padapter, pmppriv->network_macaddr);
	set_fwstate(pmlmepriv, _FW_UNDER_LINKING);
	return res;
}