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
struct timer_list {int dummy; } ;
struct mlme_ext_info {int state; scalar_t__ reauth_count; int auth_seq; scalar_t__ reassoc_count; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;
struct TYPE_2__ {int /*<<< orphan*/  link_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 scalar_t__ REASSOC_LIMIT ; 
 int /*<<< orphan*/  REASSOC_TO ; 
 scalar_t__ REAUTH_LIMIT ; 
 int /*<<< orphan*/  REAUTH_TO ; 
 int WIFI_FW_ASSOC_STATE ; 
 int WIFI_FW_AUTH_NULL ; 
 int WIFI_FW_AUTH_STATE ; 
 void* WIFI_FW_NULL_STATE ; 
 struct adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  issue_assocreq (struct adapter*) ; 
 int /*<<< orphan*/  issue_auth (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ mlmeextpriv ; 
 struct adapter* padapter ; 
 int /*<<< orphan*/  report_join_res (struct adapter*,int) ; 
 int /*<<< orphan*/  set_link_timer (struct mlme_ext_priv*,int /*<<< orphan*/ ) ; 

void link_timer_hdl(struct timer_list *t)
{
	struct adapter *padapter =
		from_timer(padapter, t, mlmeextpriv.link_timer);
	/* static unsigned int		rx_pkt = 0; */
	/* static u64				tx_cnt = 0; */
	/* struct xmit_priv 	*pxmitpriv = &(padapter->xmitpriv); */
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	/* struct sta_priv 	*pstapriv = &padapter->stapriv; */


	if (pmlmeinfo->state & WIFI_FW_AUTH_NULL) {
		DBG_871X("link_timer_hdl:no beacon while connecting\n");
		pmlmeinfo->state = WIFI_FW_NULL_STATE;
		report_join_res(padapter, -3);
	} else if (pmlmeinfo->state & WIFI_FW_AUTH_STATE) {
		/* re-auth timer */
		if (++pmlmeinfo->reauth_count > REAUTH_LIMIT) {
			/* if (pmlmeinfo->auth_algo != dot11AuthAlgrthm_Auto) */
			/*  */
				pmlmeinfo->state = 0;
				report_join_res(padapter, -1);
				return;
			/*  */
			/* else */
			/*  */
			/* 	pmlmeinfo->auth_algo = dot11AuthAlgrthm_Shared; */
			/* 	pmlmeinfo->reauth_count = 0; */
			/*  */
		}

		DBG_871X("link_timer_hdl: auth timeout and try again\n");
		pmlmeinfo->auth_seq = 1;
		issue_auth(padapter, NULL, 0);
		set_link_timer(pmlmeext, REAUTH_TO);
	} else if (pmlmeinfo->state & WIFI_FW_ASSOC_STATE) {
		/* re-assoc timer */
		if (++pmlmeinfo->reassoc_count > REASSOC_LIMIT) {
			pmlmeinfo->state = WIFI_FW_NULL_STATE;
			report_join_res(padapter, -2);
			return;
		}

		DBG_871X("link_timer_hdl: assoc timeout and try again\n");
		issue_assocreq(padapter);
		set_link_timer(pmlmeext, REASSOC_TO);
	}

	return;
}