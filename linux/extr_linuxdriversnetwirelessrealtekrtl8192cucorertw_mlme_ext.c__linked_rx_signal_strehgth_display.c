#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {int rxpwdb; int rssi; int signal_strength; int signal_qual; int FalseAlmCnt_all; scalar_t__ last_rx_bytes; scalar_t__ rx_bytes; int /*<<< orphan*/ * RxRssi; int /*<<< orphan*/ * RxSNRdB; } ;
struct TYPE_8__ {int /*<<< orphan*/  cur_channel; int /*<<< orphan*/  cur_bwmode; } ;
struct TYPE_10__ {TYPE_2__ recvpriv; TYPE_1__ mlmeextpriv; int /*<<< orphan*/  mlmepriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,...) ; 
 int /*<<< orphan*/  HAL_DEF_UNDERCORATEDSMOOTHEDPWDB ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_hal_get_def_var (TYPE_3__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtw_read16 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  rtw_read8 (TYPE_3__*,int) ; 

void _linked_rx_signal_strehgth_display(_adapter *padapter)
{
	int	UndecoratedSmoothedPWDB;
	
#ifdef CONFIG_CONCURRENT_MODE
	PADAPTER pbuddy_adapter = padapter->pbuddy_adapter;
	DBG_871X("============ pbuddy_adapter linked status check ===================\n");
	DBG_871X("buddy_adapter_type=%d\n", pbuddy_adapter->adapter_type);
	DBG_871X("pbuddy_adapter pathA Rx SNRdb:%d\n",pbuddy_adapter->recvpriv.RxSNRdB[0]);
	DBG_871X("pbuddy_adapter pathA Rx PWDB:%d\n",pbuddy_adapter->recvpriv.rxpwdb);
	DBG_871X("pbuddy_adapter pathA Rx RSSI:%d,pathB Rx RSSI:%d\n"
	,pbuddy_adapter->recvpriv.RxRssi[0],pbuddy_adapter->recvpriv.RxRssi[1]);
	rtw_hal_get_def_var(pbuddy_adapter, HAL_DEF_UNDERCORATEDSMOOTHEDPWDB, &UndecoratedSmoothedPWDB);
	DBG_871X("pbuddy_adapter UndecoratedSmoothedPWDB:%d\n",UndecoratedSmoothedPWDB);
	DBG_871X("Rx RSSI:%d\n",pbuddy_adapter->recvpriv.rssi);
	DBG_871X("Rx Signal_strength:%d\n",pbuddy_adapter->recvpriv.signal_strength);
	DBG_871X("Rx Signal_qual:%d \n",pbuddy_adapter->recvpriv.signal_qual);
	DBG_871X("============ linked status check ===================\n");
	DBG_871X("adapter_type=%d\n", padapter->adapter_type);
#else //CONFIG_CONCURRENT_MODE
	DBG_871X("============ linked status check ===================\n");
#endif //CONFIG_CONCURRENT_MODE
	DBG_871X("pathA Rx SNRdb:%d, pathB Rx SNRdb:%d\n",padapter->recvpriv.RxSNRdB[0], padapter->recvpriv.RxSNRdB[1]);
	DBG_871X("pathA Rx PWDB:%d\n",padapter->recvpriv.rxpwdb);
	DBG_871X("pathA Rx RSSI:%d,pathB Rx RSSI:%d\n",padapter->recvpriv.RxRssi[0],padapter->recvpriv.RxRssi[1]);
	rtw_hal_get_def_var(padapter, HAL_DEF_UNDERCORATEDSMOOTHEDPWDB, &UndecoratedSmoothedPWDB);
	DBG_871X("UndecoratedSmoothedPWDB:%d\n",UndecoratedSmoothedPWDB);
	DBG_871X("Rx RSSI:%d\n",padapter->recvpriv.rssi);
	DBG_871X("Rx Signal_strength:%d\n",padapter->recvpriv.signal_strength);
	DBG_871X("Rx Signal_qual:%d \n",padapter->recvpriv.signal_qual);
	if ( check_fwstate( &padapter->mlmepriv,  _FW_LINKED ))
	{
		DBG_871X("bw mode: %d, channel: %d\n", padapter->mlmeextpriv.cur_bwmode, padapter->mlmeextpriv.cur_channel );
		DBG_871X("received bytes = %d\n", (u32) (padapter->recvpriv.rx_bytes - padapter->recvpriv.last_rx_bytes ) );
	}
	DBG_871X("============ linked status check ===================\n");
	DBG_871X(" DIG PATH-A(0x%02x), PATH-B(0x%02x)\n",rtw_read8(padapter,0xc50),rtw_read8(padapter,0xc58));
	DBG_871X(" OFDM -Alarm DA2(0x%04x),DA4(0x%04x),DA6(0x%04x),DA8(0x%04x)\n",
		rtw_read16(padapter,0xDA2),rtw_read16(padapter,0xDA4),rtw_read16(padapter,0xDA6),rtw_read16(padapter,0xDA8));

	DBG_871X(" CCK -Alarm A5B(0x%02x),A5C(0x%02x)\n",rtw_read8(padapter,0xA5B),rtw_read8(padapter,0xA5C));
	DBG_871X(" FalseAlmCnt_all(%d)\n",padapter->recvpriv.FalseAlmCnt_all);
	
}