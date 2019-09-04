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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct stadel_event {int mac_id; scalar_t__ rsvd; int /*<<< orphan*/  macaddr; } ;
struct sta_info {scalar_t__ mac_id; } ;
struct mlme_ext_priv {int /*<<< orphan*/  event_seq; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int cmdsz; scalar_t__ rspsz; int /*<<< orphan*/ * rsp; int /*<<< orphan*/ * parmbuf; int /*<<< orphan*/  cmdcode; int /*<<< orphan*/  list; } ;
struct C2HEvent_Header {int len; int /*<<< orphan*/  seq; int /*<<< orphan*/  ID; } ;
struct TYPE_3__ {int /*<<< orphan*/  stapriv; struct cmd_priv cmdpriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INC_RETURN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DBG_871X (char*,int) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN_EVT_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _DelSTA ; 
 int /*<<< orphan*/  _Set_MLME_EVT ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 struct sta_info* rtw_get_stainfo (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtw_zmalloc (int) ; 

void report_del_sta_event(_adapter *padapter, unsigned char* MacAddr, unsigned short reason)
{
	struct cmd_obj *pcmd_obj;
	u8	*pevtcmd;
	u32 cmdsz;
	struct sta_info *psta;
	int	mac_id;
	struct stadel_event			*pdel_sta_evt;
	struct C2HEvent_Header	*pc2h_evt_hdr;
	struct mlme_ext_priv		*pmlmeext = &padapter->mlmeextpriv;
	struct cmd_priv *pcmdpriv = &padapter->cmdpriv;

	if ((pcmd_obj = (struct cmd_obj*)rtw_zmalloc(sizeof(struct cmd_obj))) == NULL)
	{
		return;
	}

	cmdsz = (sizeof(struct stadel_event) + sizeof(struct C2HEvent_Header));
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
	pc2h_evt_hdr->len = sizeof(struct stadel_event);
	pc2h_evt_hdr->ID = GEN_EVT_CODE(_DelSTA);
	pc2h_evt_hdr->seq = ATOMIC_INC_RETURN(&pmlmeext->event_seq);

	pdel_sta_evt = (struct stadel_event*)(pevtcmd + sizeof(struct C2HEvent_Header));
	_rtw_memcpy((unsigned char *)(&(pdel_sta_evt->macaddr)), MacAddr, ETH_ALEN);
	_rtw_memcpy((unsigned char *)(pdel_sta_evt->rsvd),(unsigned char *)(&reason),2);


	psta = rtw_get_stainfo(&padapter->stapriv, MacAddr);
	if(psta)
		mac_id = (int)psta->mac_id;	
	else
		mac_id = (-1);

	pdel_sta_evt->mac_id = mac_id;

	DBG_871X("report_del_sta_event: delete STA, mac_id=%d\n", mac_id);

	rtw_enqueue_cmd(pcmdpriv, pcmd_obj);

	return;
}