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
typedef  union recv_frame {int dummy; } recv_frame ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct survey_event {int /*<<< orphan*/  bss; } ;
struct TYPE_5__ {int /*<<< orphan*/  bss_cnt; } ;
struct mlme_ext_priv {TYPE_1__ sitesurvey_res; int /*<<< orphan*/  event_seq; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int cmdsz; scalar_t__ rspsz; int /*<<< orphan*/ * rsp; int /*<<< orphan*/ * parmbuf; int /*<<< orphan*/  cmdcode; int /*<<< orphan*/  list; } ;
struct C2HEvent_Header {int len; int /*<<< orphan*/  seq; int /*<<< orphan*/  ID; } ;
struct TYPE_6__ {struct cmd_priv cmdpriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_2__ _adapter ;
typedef  int /*<<< orphan*/  WLAN_BSSID_EX ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INC_RETURN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN_EVT_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ _FAIL ; 
 int /*<<< orphan*/  _Set_MLME_EVT ; 
 int /*<<< orphan*/  _Survey ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 scalar_t__ collect_bss_info (TYPE_2__*,union recv_frame*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

void report_survey_event(_adapter *padapter, union recv_frame *precv_frame)
{
	struct cmd_obj *pcmd_obj;
	u8	*pevtcmd;
	u32 cmdsz;
	struct survey_event	*psurvey_evt;
	struct C2HEvent_Header *pc2h_evt_hdr;
	struct mlme_ext_priv *pmlmeext;
	struct cmd_priv *pcmdpriv;
	//u8 *pframe = precv_frame->u.hdr.rx_data;
	//uint len = precv_frame->u.hdr.len;

	if(!padapter)
		return;

	pmlmeext = &padapter->mlmeextpriv;
	pcmdpriv = &padapter->cmdpriv;
	

	if ((pcmd_obj = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj))) == NULL)
	{
		return;
	}

	cmdsz = (sizeof(struct survey_event) + sizeof(struct C2HEvent_Header));
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
	pc2h_evt_hdr->len = sizeof(struct survey_event);
	pc2h_evt_hdr->ID = GEN_EVT_CODE(_Survey);
	pc2h_evt_hdr->seq = ATOMIC_INC_RETURN(&pmlmeext->event_seq);

	psurvey_evt = (struct survey_event*)(pevtcmd + sizeof(struct C2HEvent_Header));

	if (collect_bss_info(padapter, precv_frame, (WLAN_BSSID_EX *)&psurvey_evt->bss) == _FAIL)
	{
		rtw_mfree((u8 *)pcmd_obj, sizeof(struct cmd_obj));
		rtw_mfree((u8 *)pevtcmd, cmdsz);
		return;
	}

#ifdef CONFIG_80211D
	process_80211d(padapter, &psurvey_evt->bss);
#endif

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);

	pmlmeext->sitesurvey_res.bss_cnt++;

	return;

}