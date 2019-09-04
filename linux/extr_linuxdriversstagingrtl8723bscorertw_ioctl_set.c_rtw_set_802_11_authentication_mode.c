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
typedef  int u8 ;
struct security_priv {int ndisauthtype; int /*<<< orphan*/  dot11AuthAlgrthm; } ;
struct adapter {struct security_priv securitypriv; } ;
typedef  enum NDIS_802_11_AUTHENTICATION_MODE { ____Placeholder_NDIS_802_11_AUTHENTICATION_MODE } NDIS_802_11_AUTHENTICATION_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_set_c_ ; 
 int /*<<< orphan*/  dot11AuthAlgrthm_8021X ; 
 int rtw_set_auth (struct adapter*,struct security_priv*) ; 

u8 rtw_set_802_11_authentication_mode(struct adapter *padapter, enum NDIS_802_11_AUTHENTICATION_MODE authmode)
{
	struct security_priv *psecuritypriv = &padapter->securitypriv;
	int res;
	u8 ret;

	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("set_802_11_auth.mode(): mode =%x\n", authmode));

	psecuritypriv->ndisauthtype = authmode;

	RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_info_, ("rtw_set_802_11_authentication_mode:psecuritypriv->ndisauthtype =%d", psecuritypriv->ndisauthtype));

	if (psecuritypriv->ndisauthtype > 3)
		psecuritypriv->dot11AuthAlgrthm = dot11AuthAlgrthm_8021X;

	res = rtw_set_auth(padapter, psecuritypriv);

	if (res == _SUCCESS)
		ret = true;
	else
		ret = false;

	return ret;
}