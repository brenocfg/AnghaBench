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
typedef  int u8 ;
struct TYPE_3__ {int level; int /*<<< orphan*/  updated; } ;
struct TYPE_4__ {TYPE_1__ qual; } ;
struct atmel_private {int firmware_type; TYPE_2__ wstats; } ;

/* Variables and functions */
#define  ATMEL_FW_TYPE_502E 128 
 int /*<<< orphan*/  IW_QUAL_LEVEL_INVALID ; 
 int /*<<< orphan*/  IW_QUAL_LEVEL_UPDATED ; 

__attribute__((used)) static void smooth_rssi(struct atmel_private *priv, u8 rssi)
{
	u8 old = priv->wstats.qual.level;
	u8 max_rssi = 42; /* 502-rmfd-revd max by experiment, default for now */

	switch (priv->firmware_type) {
	case ATMEL_FW_TYPE_502E:
		max_rssi = 63; /* 502-rmfd-reve max by experiment */
		break;
	default:
		break;
	}

	rssi = rssi * 100 / max_rssi;
	if ((rssi + old) % 2)
		priv->wstats.qual.level = (rssi + old) / 2 + 1;
	else
		priv->wstats.qual.level = (rssi + old) / 2;
	priv->wstats.qual.updated |= IW_QUAL_LEVEL_UPDATED;
	priv->wstats.qual.updated &= ~IW_QUAL_LEVEL_INVALID;
}