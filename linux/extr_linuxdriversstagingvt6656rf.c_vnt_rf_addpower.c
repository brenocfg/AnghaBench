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
struct vnt_private {int current_rssi; scalar_t__ rf_type; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ RF_VT3226D0 ; 

__attribute__((used)) static u8 vnt_rf_addpower(struct vnt_private *priv)
{
	s32 rssi = -priv->current_rssi;

	if (!rssi)
		return 7;

	if (priv->rf_type == RF_VT3226D0) {
		if (rssi < -70)
			return 9;
		else if (rssi < -65)
			return 7;
		else if (rssi < -60)
			return 5;
	} else {
		if (rssi < -80)
			return 9;
		else if (rssi < -75)
			return 7;
		else if (rssi < -70)
			return 5;
	}

	return 0;
}