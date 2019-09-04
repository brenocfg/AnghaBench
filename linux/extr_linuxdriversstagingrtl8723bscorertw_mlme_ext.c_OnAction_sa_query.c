#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int pkt_len; } ;
struct TYPE_3__ {int* rx_data; struct rx_pkt_attrib attrib; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int u8 ;
struct mlme_ext_priv {int /*<<< orphan*/  sa_query_timer; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int /*<<< orphan*/  GetAddr2Ptr (int*) ; 
 int WLAN_HDR_A3_LEN ; 
 unsigned int _SUCCESS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  issue_action_SA_Query (struct adapter*,int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  memcpy (unsigned short*,int*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

unsigned int OnAction_sa_query(struct adapter *padapter, union recv_frame *precv_frame)
{
	u8 *pframe = precv_frame->u.hdr.rx_data;
	struct rx_pkt_attrib *pattrib = &precv_frame->u.hdr.attrib;
	struct mlme_ext_priv *pmlmeext = &(padapter->mlmeextpriv);
	unsigned short tid;
	/* Baron */

	DBG_871X("OnAction_sa_query\n");

	switch (pframe[WLAN_HDR_A3_LEN+1]) {
	case 0: /* SA Query req */
		memcpy(&tid, &pframe[WLAN_HDR_A3_LEN+2], sizeof(unsigned short));
		DBG_871X("OnAction_sa_query request, action =%d, tid =%04x\n", pframe[WLAN_HDR_A3_LEN+1], tid);
		issue_action_SA_Query(padapter, GetAddr2Ptr(pframe), 1, tid);
		break;

	case 1: /* SA Query rsp */
		del_timer_sync(&pmlmeext->sa_query_timer);
		DBG_871X("OnAction_sa_query response, action =%d, tid =%04x, cancel timer\n", pframe[WLAN_HDR_A3_LEN+1], pframe[WLAN_HDR_A3_LEN+2]);
		break;
	default:
		break;
	}
	if (0) {
		int pp;
		printk("pattrib->pktlen = %d =>", pattrib->pkt_len);
		for (pp = 0; pp < pattrib->pkt_len; pp++)
			printk(" %02x ", pframe[pp]);
		printk("\n");
	}

	return _SUCCESS;
}