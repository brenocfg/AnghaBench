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
struct mlme_ext_info {int auth_seq; scalar_t__ link_count; scalar_t__ reassoc_count; scalar_t__ reauth_count; int /*<<< orphan*/  state; } ;
struct mlme_ext_priv {scalar_t__ retry; int /*<<< orphan*/  link_timer; struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X_LEVEL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  REAUTH_TO ; 
 int /*<<< orphan*/  WIFI_FW_AUTH_NULL ; 
 int /*<<< orphan*/  WIFI_FW_AUTH_STATE ; 
 int /*<<< orphan*/  _drv_always_ ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  issue_auth (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_link_timer (struct mlme_ext_priv*,int /*<<< orphan*/ ) ; 

void start_clnt_auth(struct adapter *padapter)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	del_timer_sync(&pmlmeext->link_timer);

	pmlmeinfo->state &= (~WIFI_FW_AUTH_NULL);
	pmlmeinfo->state |= WIFI_FW_AUTH_STATE;

	pmlmeinfo->auth_seq = 1;
	pmlmeinfo->reauth_count = 0;
	pmlmeinfo->reassoc_count = 0;
	pmlmeinfo->link_count = 0;
	pmlmeext->retry = 0;


	DBG_871X_LEVEL(_drv_always_, "start auth\n");
	issue_auth(padapter, NULL, 0);

	set_link_timer(pmlmeext, REAUTH_TO);

}