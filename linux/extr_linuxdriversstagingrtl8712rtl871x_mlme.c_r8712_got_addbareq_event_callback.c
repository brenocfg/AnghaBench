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
typedef  int /*<<< orphan*/  u8 ;
struct sta_priv {int dummy; } ;
struct sta_info {struct recv_reorder_ctrl* recvreorder_ctrl; } ;
struct recv_reorder_ctrl {int indicate_seq; } ;
struct _adapter {struct sta_priv stapriv; } ;
struct ADDBA_Req_Report_parm {size_t tid; int /*<<< orphan*/  MacAddress; } ;

/* Variables and functions */
 struct sta_info* r8712_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 

void r8712_got_addbareq_event_callback(struct _adapter *adapter, u8 *pbuf)
{
	struct	ADDBA_Req_Report_parm *pAddbareq_pram =
			 (struct ADDBA_Req_Report_parm *)pbuf;
	struct	sta_info *psta;
	struct	sta_priv *pstapriv = &adapter->stapriv;
	struct	recv_reorder_ctrl *precvreorder_ctrl = NULL;

	psta = r8712_get_stainfo(pstapriv, pAddbareq_pram->MacAddress);
	if (psta) {
		precvreorder_ctrl =
			 &psta->recvreorder_ctrl[pAddbareq_pram->tid];
		/* set the indicate_seq to 0xffff so that the rx reorder
		 * can store any following data packet.
		 */
		precvreorder_ctrl->indicate_seq = 0xffff;
	}
}