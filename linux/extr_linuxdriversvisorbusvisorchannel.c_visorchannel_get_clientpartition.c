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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  partition_handle; } ;
struct visorchannel {TYPE_1__ chan_hdr; } ;

/* Variables and functions */

u64 visorchannel_get_clientpartition(struct visorchannel *channel)
{
	return channel->chan_hdr.partition_handle;
}