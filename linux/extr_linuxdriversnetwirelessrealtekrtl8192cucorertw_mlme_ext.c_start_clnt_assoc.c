#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlme_ext_info {int state; } ;
struct mlme_ext_priv {int /*<<< orphan*/  link_timer; struct mlme_ext_info mlmext_info; } ;
struct TYPE_4__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  REASSOC_TO ; 
 int WIFI_FW_ASSOC_STATE ; 
 int WIFI_FW_AUTH_NULL ; 
 int WIFI_FW_AUTH_STATE ; 
 int WIFI_FW_AUTH_SUCCESS ; 
 int /*<<< orphan*/  _cancel_timer_ex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  issue_assocreq (TYPE_1__*) ; 
 int /*<<< orphan*/  set_link_timer (struct mlme_ext_priv*,int /*<<< orphan*/ ) ; 

void start_clnt_assoc(_adapter* padapter)
{
	struct mlme_ext_priv	*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);

	_cancel_timer_ex(&pmlmeext->link_timer);

	pmlmeinfo->state &= (~(WIFI_FW_AUTH_NULL | WIFI_FW_AUTH_STATE));
	pmlmeinfo->state |= (WIFI_FW_AUTH_SUCCESS | WIFI_FW_ASSOC_STATE);

	issue_assocreq(padapter);

	set_link_timer(pmlmeext, REASSOC_TO);
}