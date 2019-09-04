#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mlme_ext_info {int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {int /*<<< orphan*/  event_seq; struct mlme_ext_info mlmext_info; } ;
struct TYPE_5__ {int join_res; int aid; int /*<<< orphan*/  network; } ;
struct joinbss_event {TYPE_1__ network; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int cmdsz; scalar_t__ rspsz; int /*<<< orphan*/ * rsp; int /*<<< orphan*/ * parmbuf; int /*<<< orphan*/  cmdcode; int /*<<< orphan*/  list; } ;
struct C2HEvent_Header {int len; int /*<<< orphan*/  seq; int /*<<< orphan*/  ID; } ;
struct TYPE_6__ {struct cmd_priv cmdpriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  int /*<<< orphan*/  WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INC_RETURN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DBG_871X (char*,int) ; 
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN_EVT_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _JoinBss ; 
 int /*<<< orphan*/  _Set_MLME_EVT ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_joinbss_event_prehandle (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

void report_join_res(_adapter *padapter, int res)
{
	struct cmd_obj *pcmd_obj;
	u8	*pevtcmd;
	u32 cmdsz;
	struct joinbss_event		*pjoinbss_evt;
	struct C2HEvent_Header	*pc2h_evt_hdr;
	struct mlme_ext_priv		*pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info	*pmlmeinfo = &(pmlmeext->mlmext_info);
	struct cmd_priv *pcmdpriv = &padapter->cmdpriv;

	if ((pcmd_obj = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj))) == NULL)
	{
		return;
	}

	cmdsz = (sizeof(struct joinbss_event) + sizeof(struct C2HEvent_Header));
	if ((pevtcmd = (u8*)rtw_zmalloc(cmdsz)) == NULL)
	{
		rtw_mfree((u8 *)pcmd_obj, sizeof(struct cmd_obj));
		return;
	}

	_rtw_init_listhead(&pcmd_obj->list);

	pcmd_obj->cmdcode = GEN_CMD_CODE(_Set_MLME_EVT);
	pcmd_obj->cmdsz = cmdsz;
	pcmd_obj->parmbuf = pevtcmd;

	pcmd_obj->rsp = NULL;
	pcmd_obj->rspsz  = 0;

	pc2h_evt_hdr = (struct C2HEvent_Header*)(pevtcmd);
	pc2h_evt_hdr->len = sizeof(struct joinbss_event);
	pc2h_evt_hdr->ID = GEN_EVT_CODE(_JoinBss);
	pc2h_evt_hdr->seq = ATOMIC_INC_RETURN(&pmlmeext->event_seq);

	pjoinbss_evt = (struct joinbss_event*)(pevtcmd + sizeof(struct C2HEvent_Header));
	_rtw_memcpy((unsigned char *)(&(pjoinbss_evt->network.network)), &(pmlmeinfo->network), sizeof(WLAN_BSSID_EX));
	pjoinbss_evt->network.join_res 	= pjoinbss_evt->network.aid = res;

	DBG_871X("report_join_res(%d)\n", res);
	
	
	rtw_joinbss_event_prehandle(padapter, (u8 *)&pjoinbss_evt->network);
	
	
	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);

	return;

}