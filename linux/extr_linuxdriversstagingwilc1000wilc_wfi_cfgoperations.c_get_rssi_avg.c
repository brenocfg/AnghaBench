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
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_2__ {size_t index; scalar_t__* samples; scalar_t__ full; } ;
struct network_info {TYPE_1__ rssi_history; } ;

/* Variables and functions */
 size_t NUM_RSSI ; 

__attribute__((used)) static u32 get_rssi_avg(struct network_info *network_info)
{
	u8 i;
	int rssi_v = 0;
	u8 num_rssi = (network_info->rssi_history.full) ?
		       NUM_RSSI : (network_info->rssi_history.index);

	for (i = 0; i < num_rssi; i++)
		rssi_v += network_info->rssi_history.samples[i];

	rssi_v /= num_rssi;
	return rssi_v;
}