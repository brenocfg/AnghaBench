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
struct stainfo_stats {int rx_bytes; int /*<<< orphan*/  rx_data_pkts; } ;
struct sta_info {struct stainfo_stats sta_stats; } ;
struct rx_pkt_attrib {int /*<<< orphan*/  dst; } ;
struct recv_priv {int rx_bytes; } ;
struct recv_frame {struct sta_info* psta; TYPE_1__* pkt; struct rx_pkt_attrib attrib; } ;
struct TYPE_5__ {int /*<<< orphan*/  NumRxUnicastOkInPeriod; int /*<<< orphan*/  NumRxOkInPeriod; } ;
struct TYPE_6__ {TYPE_2__ LinkDetectInfo; } ;
struct adapter {TYPE_3__ mlmepriv; struct recv_priv recvpriv; } ;
struct TYPE_4__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void count_rx_stats(struct adapter *padapter,
			   struct recv_frame *prframe,
			   struct sta_info *sta)
{
	int	sz;
	struct sta_info		*psta = NULL;
	struct stainfo_stats	*pstats = NULL;
	struct rx_pkt_attrib	*pattrib = &prframe->attrib;
	struct recv_priv	*precvpriv = &padapter->recvpriv;

	sz = prframe->pkt->len;
	precvpriv->rx_bytes += sz;

	padapter->mlmepriv.LinkDetectInfo.NumRxOkInPeriod++;

	if (!is_multicast_ether_addr(pattrib->dst))
		padapter->mlmepriv.LinkDetectInfo.NumRxUnicastOkInPeriod++;

	if (sta)
		psta = sta;
	else
		psta = prframe->psta;

	if (psta) {
		pstats = &psta->sta_stats;

		pstats->rx_data_pkts++;
		pstats->rx_bytes += sz;
	}
}