#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {scalar_t__ signal_qual; } ;
struct TYPE_7__ {struct rx_pkt_attrib attrib; } ;
struct TYPE_8__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_9__ {size_t total_num; int* elements; size_t index; int total_val; } ;
struct TYPE_10__ {scalar_t__ signal_qual; TYPE_3__ signal_qual_data; } ;
struct TYPE_11__ {TYPE_4__ recvpriv; } ;
typedef  TYPE_5__ _adapter ;

/* Variables and functions */
 size_t PHY_LINKQUALITY_SLID_WIN_MAX ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 

__attribute__((used)) static void process_link_qual(_adapter *padapter,union recv_frame *prframe)
{
	u32	last_evm=0, tmpVal;
 	struct rx_pkt_attrib *pattrib;
#ifdef CONFIG_NEW_SIGNAL_STAT_PROCESS
	struct signal_stat * signal_stat;
#endif //CONFIG_NEW_SIGNAL_STAT_PROCESS

	if(prframe == NULL || padapter==NULL){
		return;
	}

	pattrib = &prframe->u.hdr.attrib;
#ifdef CONFIG_NEW_SIGNAL_STAT_PROCESS
	signal_stat = &padapter->recvpriv.signal_qual_data;
#endif //CONFIG_NEW_SIGNAL_STAT_PROCESS

	//DBG_8192C("process_link_qual=> pattrib->signal_qual(%d)\n ",pattrib->signal_qual);

#ifdef CONFIG_NEW_SIGNAL_STAT_PROCESS
	if(signal_stat->update_req) {
		signal_stat->total_num = 0;
		signal_stat->total_val = 0;
		signal_stat->update_req = 0;
	}

	signal_stat->total_num++;
	signal_stat->total_val  += pattrib->signal_qual;
	signal_stat->avg_val = signal_stat->total_val / signal_stat->total_num;
	
#else //CONFIG_NEW_SIGNAL_STAT_PROCESS
	if(pattrib->signal_qual != 0)
	{
			//
			// 1. Record the general EVM to the sliding window.
			//
			if(padapter->recvpriv.signal_qual_data.total_num++ >= PHY_LINKQUALITY_SLID_WIN_MAX)
			{
				padapter->recvpriv.signal_qual_data.total_num = PHY_LINKQUALITY_SLID_WIN_MAX;
				last_evm = padapter->recvpriv.signal_qual_data.elements[padapter->recvpriv.signal_qual_data.index];
				padapter->recvpriv.signal_qual_data.total_val -= last_evm;
			}
			padapter->recvpriv.signal_qual_data.total_val += pattrib->signal_qual;

			padapter->recvpriv.signal_qual_data.elements[padapter->recvpriv.signal_qual_data.index++] = pattrib->signal_qual;
			if(padapter->recvpriv.signal_qual_data.index >= PHY_LINKQUALITY_SLID_WIN_MAX)
				padapter->recvpriv.signal_qual_data.index = 0;

			RT_TRACE(_module_rtl871x_recv_c_,_drv_info_,("Total SQ=%d  pattrib->signal_qual= %d\n", padapter->recvpriv.signal_qual_data.total_val, pattrib->signal_qual));

			// <1> Showed on UI for user, in percentage.
			tmpVal = padapter->recvpriv.signal_qual_data.total_val/padapter->recvpriv.signal_qual_data.total_num;
			padapter->recvpriv.signal_qual=(u8)tmpVal;

	}
	else
	{
		RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,(" pattrib->signal_qual =%d\n", pattrib->signal_qual));
	}
#endif //CONFIG_NEW_SIGNAL_STAT_PROCESS

}