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
typedef  int u8 ;
struct sta_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sta_update_last_rx_pkts (struct sta_info*) ; 

u8 chk_sta_is_alive(struct sta_info *psta)
{
	#ifdef DBG_EXPIRATION_CHK
	DBG_871X(
		"sta:"MAC_FMT", rssi:%d, rx:"STA_PKTS_FMT", expire_to:%u, %s%ssq_len:%u\n"
		, MAC_ARG(psta->hwaddr)
		, psta->rssi_stat.UndecoratedSmoothedPWDB
		/*  STA_RX_PKTS_ARG(psta) */
		, STA_RX_PKTS_DIFF_ARG(psta)
		, psta->expire_to
		, psta->state&WIFI_SLEEP_STATE?"PS, ":""
		, psta->state&WIFI_STA_ALIVE_CHK_STATE?"SAC, ":""
		, psta->sleepq_len
	);
	#endif

	sta_update_last_rx_pkts(psta);

	return true;
}