#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ SignalQuality; } ;
struct rx_pkt_attrib {TYPE_4__ phy_info; } ;
struct TYPE_5__ {struct rx_pkt_attrib attrib; } ;
struct TYPE_6__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct signal_stat {int total_num; int total_val; int avg_val; scalar_t__ update_req; } ;
struct TYPE_7__ {struct signal_stat signal_qual_data; } ;
struct adapter {TYPE_3__ recvpriv; } ;

/* Variables and functions */

__attribute__((used)) static void process_link_qual(struct adapter *padapter, union recv_frame *prframe)
{
	struct rx_pkt_attrib *pattrib;
	struct signal_stat *signal_stat;

	if (prframe == NULL || padapter == NULL)
		return;

	pattrib = &prframe->u.hdr.attrib;
	signal_stat = &padapter->recvpriv.signal_qual_data;

	/* DBG_8192C("process_link_qual => pattrib->signal_qual(%d)\n ", pattrib->signal_qual); */

	if (signal_stat->update_req) {
		signal_stat->total_num = 0;
		signal_stat->total_val = 0;
		signal_stat->update_req = 0;
	}

	signal_stat->total_num++;
	signal_stat->total_val  += pattrib->phy_info.SignalQuality;
	signal_stat->avg_val = signal_stat->total_val / signal_stat->total_num;
}