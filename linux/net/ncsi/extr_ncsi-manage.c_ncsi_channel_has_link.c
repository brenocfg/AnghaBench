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
struct ncsi_channel {TYPE_1__* modes; } ;
struct TYPE_2__ {int* data; } ;

/* Variables and functions */
 size_t NCSI_MODE_LINK ; 

bool ncsi_channel_has_link(struct ncsi_channel *channel)
{
	return !!(channel->modes[NCSI_MODE_LINK].data[2] & 0x1);
}