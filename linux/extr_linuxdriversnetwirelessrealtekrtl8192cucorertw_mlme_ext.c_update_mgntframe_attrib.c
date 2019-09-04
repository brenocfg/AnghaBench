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
struct pkt_attrib {int hdrlen; int nr_frags; int priority; int qsel; int raid; int /*<<< orphan*/  retry_ctrl; int /*<<< orphan*/  seqnum; void* sgi; int /*<<< orphan*/  ch_offset; int /*<<< orphan*/  bwmode; void* ht_en; void* qos_en; void* bswenc; int /*<<< orphan*/  encrypt; scalar_t__ pktlen; scalar_t__ mac_id; } ;
struct mlme_ext_priv {int cur_wireless_mode; int /*<<< orphan*/  mgnt_seq; } ;
struct TYPE_3__ {struct mlme_ext_priv mlmeextpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int /*<<< orphan*/  HT_CHANNEL_WIDTH_20 ; 
 int WIRELESS_11B ; 
 void* _FALSE ; 
 int /*<<< orphan*/  _NO_PRIVACY_ ; 
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  _rtw_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void update_mgntframe_attrib(_adapter *padapter, struct pkt_attrib *pattrib)
{
	struct mlme_ext_priv	*pmlmeext = &(padapter->mlmeextpriv);

	_rtw_memset((u8 *)(pattrib), 0, sizeof(struct pkt_attrib));

	pattrib->hdrlen = 24;
	pattrib->nr_frags = 1;
	pattrib->priority = 7;
	pattrib->mac_id = 0;
	pattrib->qsel = 0x12;

	pattrib->pktlen = 0;

	if(pmlmeext->cur_wireless_mode & WIRELESS_11B)
		pattrib->raid = 6;//b mode
	else
		pattrib->raid = 5;//a/g mode

	pattrib->encrypt = _NO_PRIVACY_;
	pattrib->bswenc = _FALSE;	

	pattrib->qos_en = _FALSE;
	pattrib->ht_en = _FALSE;
	pattrib->bwmode = HT_CHANNEL_WIDTH_20;
	pattrib->ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;
	pattrib->sgi = _FALSE;

	pattrib->seqnum = pmlmeext->mgnt_seq;

	pattrib->retry_ctrl = _TRUE;

}