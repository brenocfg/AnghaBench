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
struct demux_packet {size_t len; TYPE_1__* avpacket; } ;
struct TYPE_2__ {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  av_shrink_packet (TYPE_1__*,size_t) ; 

void demux_packet_shorten(struct demux_packet *dp, size_t len)
{
    assert(len <= dp->len);
    av_shrink_packet(dp->avpacket, len);
    dp->len = dp->avpacket->size;
}