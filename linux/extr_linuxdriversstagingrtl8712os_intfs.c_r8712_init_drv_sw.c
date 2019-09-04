#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct security_priv {int dummy; } ;
struct TYPE_6__ {struct _adapter* padapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  tkip_timer; } ;
struct TYPE_5__ {struct _adapter* padapter; } ;
struct _adapter {TYPE_3__ stapriv; TYPE_1__ securitypriv; int /*<<< orphan*/  recvpriv; int /*<<< orphan*/  xmitpriv; int /*<<< orphan*/  evtpriv; TYPE_2__ cmdpriv; } ;

/* Variables and functions */
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _r8712_init_recv_priv (int /*<<< orphan*/ *,struct _adapter*) ; 
 int /*<<< orphan*/  _r8712_init_sta_priv (TYPE_3__*) ; 
 int /*<<< orphan*/  _r8712_init_xmit_priv (int /*<<< orphan*/ *,struct _adapter*) ; 
 scalar_t__ init_default_value (struct _adapter*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp871xinit (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_InitSwLeds (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_init_bcmc_stainfo (struct _adapter*) ; 
 scalar_t__ r8712_init_cmd_priv (TYPE_2__*) ; 
 scalar_t__ r8712_init_evt_priv (int /*<<< orphan*/ *) ; 
 scalar_t__ r8712_init_mlme_priv (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_init_pwrctrl_priv (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_use_tkipkey_handler ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 r8712_init_drv_sw(struct _adapter *padapter)
{
	if ((r8712_init_cmd_priv(&padapter->cmdpriv)) == _FAIL)
		return _FAIL;
	padapter->cmdpriv.padapter = padapter;
	if ((r8712_init_evt_priv(&padapter->evtpriv)) == _FAIL)
		return _FAIL;
	if (r8712_init_mlme_priv(padapter) == _FAIL)
		return _FAIL;
	_r8712_init_xmit_priv(&padapter->xmitpriv, padapter);
	_r8712_init_recv_priv(&padapter->recvpriv, padapter);
	memset((unsigned char *)&padapter->securitypriv, 0,
	       sizeof(struct security_priv));
	timer_setup(&padapter->securitypriv.tkip_timer,
		    r8712_use_tkipkey_handler, 0);
	_r8712_init_sta_priv(&padapter->stapriv);
	padapter->stapriv.padapter = padapter;
	r8712_init_bcmc_stainfo(padapter);
	r8712_init_pwrctrl_priv(padapter);
	mp871xinit(padapter);
	if (init_default_value(padapter) != _SUCCESS)
		return _FAIL;
	r8712_InitSwLeds(padapter);
	return _SUCCESS;
}