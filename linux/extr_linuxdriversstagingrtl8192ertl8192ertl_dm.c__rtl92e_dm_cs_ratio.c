#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ reset_count; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ PreSTAConnectState; scalar_t__ CurSTAConnectState; scalar_t__ rssi_val; scalar_t__ rssi_low_thresh; scalar_t__ curcs_ratio_state; scalar_t__ rssi_high_thresh; scalar_t__ precs_ratio_state; scalar_t__ dig_algorithm_switch; } ;

/* Variables and functions */
 scalar_t__ DIG_CS_RATIO_HIGHER ; 
 scalar_t__ DIG_CS_RATIO_LOWER ; 
 scalar_t__ DIG_STA_CONNECT ; 
 TYPE_1__ dm_digtable ; 
 int /*<<< orphan*/  rtl92e_writeb (struct net_device*,int,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_cs_ratio(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	static u8 initialized, force_write;
	static u32 reset_cnt;

	if (dm_digtable.dig_algorithm_switch) {
		initialized = 0;
		reset_cnt = 0;
	}

	if (dm_digtable.PreSTAConnectState == dm_digtable.CurSTAConnectState) {
		if (dm_digtable.CurSTAConnectState == DIG_STA_CONNECT) {
			if (dm_digtable.rssi_val <= dm_digtable.rssi_low_thresh)
				dm_digtable.curcs_ratio_state = DIG_CS_RATIO_LOWER;
			else if (dm_digtable.rssi_val >= dm_digtable.rssi_high_thresh)
				dm_digtable.curcs_ratio_state = DIG_CS_RATIO_HIGHER;
			else
				dm_digtable.curcs_ratio_state = dm_digtable.precs_ratio_state;
		} else {
			dm_digtable.curcs_ratio_state = DIG_CS_RATIO_LOWER;
		}
	} else {
		dm_digtable.curcs_ratio_state = DIG_CS_RATIO_LOWER;
	}

	if (priv->reset_count != reset_cnt) {
		force_write = 1;
		reset_cnt = priv->reset_count;
	}


	if ((dm_digtable.precs_ratio_state != dm_digtable.curcs_ratio_state) ||
	    !initialized || force_write) {
		if (dm_digtable.curcs_ratio_state == DIG_CS_RATIO_LOWER)
			rtl92e_writeb(dev, 0xa0a, 0x08);
		else if (dm_digtable.curcs_ratio_state == DIG_CS_RATIO_HIGHER)
			rtl92e_writeb(dev, 0xa0a, 0xcd);
		dm_digtable.precs_ratio_state = dm_digtable.curcs_ratio_state;
		initialized = 1;
		force_write = 0;
	}
}