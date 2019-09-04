#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int ChannelNum; } ;
typedef  TYPE_1__ RT_CHANNEL_INFO ;

/* Variables and functions */

__attribute__((used)) static int has_channel(RT_CHANNEL_INFO *channel_set,
					   u8 chanset_size,
					   u8 chan)
{
	int i;

	for (i = 0; i < chanset_size; i++) {
		if (channel_set[i].ChannelNum == chan) {
			return 1;
		}
	}

	return 0;
}