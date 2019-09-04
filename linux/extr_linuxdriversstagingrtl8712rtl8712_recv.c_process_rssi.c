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
struct rx_pkt_attrib {int signal_strength; } ;
struct TYPE_4__ {struct rx_pkt_attrib attrib; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct smooth_rssi_data {size_t total_num; int* elements; size_t index; int total_val; } ;
struct TYPE_6__ {scalar_t__ rssi; struct smooth_rssi_data signal_strength_data; } ;
struct _adapter {TYPE_3__ recvpriv; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 size_t PHY_RSSI_SLID_WIN_MAX ; 
 scalar_t__ translate2dbm (struct _adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_rssi(struct _adapter *padapter, union recv_frame *prframe)
{
	u32 last_rssi, tmp_val;
	struct rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib;
	struct smooth_rssi_data *ssd = &padapter->recvpriv.signal_strength_data;

	if (ssd->total_num++ >= PHY_RSSI_SLID_WIN_MAX) {
		ssd->total_num = PHY_RSSI_SLID_WIN_MAX;
		last_rssi = ssd->elements[ssd->index];
		ssd->total_val -= last_rssi;
	}
	ssd->total_val += pattrib->signal_strength;
	ssd->elements[ssd->index++] = pattrib->signal_strength;
	if (ssd->index >= PHY_RSSI_SLID_WIN_MAX)
		ssd->index = 0;
	tmp_val = ssd->total_val / ssd->total_num;
	padapter->recvpriv.rssi = (s8)translate2dbm(padapter, (u8)tmp_val);
}