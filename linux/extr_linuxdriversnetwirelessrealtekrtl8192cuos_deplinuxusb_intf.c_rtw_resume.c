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
struct usb_interface {int dummy; } ;
struct pwrctrl_priv {scalar_t__ bInternalAutoSuspend; } ;
struct net_device {int dummy; } ;
struct dvobj_priv {TYPE_1__* if1; } ;
struct TYPE_3__ {struct pwrctrl_priv pwrctrlpriv; struct net_device* pnetdev; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _TRUE ; 
 scalar_t__ rtw_is_earlysuspend_registered (struct pwrctrl_priv*) ; 
 int rtw_resume_process (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_set_do_late_resume (struct pwrctrl_priv*,int /*<<< orphan*/ ) ; 
 struct dvobj_priv* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int rtw_resume(struct usb_interface *pusb_intf)
{
	struct dvobj_priv *dvobj = usb_get_intfdata(pusb_intf);
	_adapter *padapter = dvobj->if1;
	struct net_device *pnetdev = padapter->pnetdev;
	struct pwrctrl_priv *pwrpriv = &padapter->pwrctrlpriv;
	 int ret = 0;

	if(pwrpriv->bInternalAutoSuspend ){
 		ret = rtw_resume_process(padapter);
	} else {
#ifdef CONFIG_RESUME_IN_WORKQUEUE
		rtw_resume_in_workqueue(pwrpriv);
#else
		if (rtw_is_earlysuspend_registered(pwrpriv)
			#ifdef CONFIG_WOWLAN
			&& !padapter->pwrctrlpriv.wowlan_mode
			#endif /* CONFIG_WOWLAN */
		) {
			/* jeff: bypass resume here, do in late_resume */
			rtw_set_do_late_resume(pwrpriv, _TRUE);
		} else {
			ret = rtw_resume_process(padapter);
		}
#endif /* CONFIG_RESUME_IN_WORKQUEUE */
	}

	return ret;

}