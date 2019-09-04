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
typedef  size_t u16 ;
struct TYPE_2__ {size_t rates_len; int* rates; } ;
struct rtllib_device {int /*<<< orphan*/  dev; TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtllib_is_cck_rate (int) ; 

u8
MgntQuery_TxRateExcludeCCKRates(struct rtllib_device *ieee)
{
	u16	i;
	u8	QueryRate = 0;
	u8	BasicRate;


	for (i = 0; i < ieee->current_network.rates_len; i++) {
		BasicRate = ieee->current_network.rates[i]&0x7F;
		if (!rtllib_is_cck_rate(BasicRate)) {
			if (QueryRate == 0) {
				QueryRate = BasicRate;
			} else {
				if (BasicRate < QueryRate)
					QueryRate = BasicRate;
			}
		}
	}

	if (QueryRate == 0) {
		QueryRate = 12;
		netdev_info(ieee->dev, "No BasicRate found!!\n");
	}
	return QueryRate;
}