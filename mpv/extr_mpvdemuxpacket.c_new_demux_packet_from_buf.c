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
struct demux_packet {int dummy; } ;
struct AVBufferRef {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {struct AVBufferRef* buf; int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ AVPacket ;

/* Variables and functions */
 struct demux_packet* new_demux_packet_from_avpacket (TYPE_1__*) ; 

struct demux_packet *new_demux_packet_from_buf(struct AVBufferRef *buf)
{
    if (!buf)
        return NULL;
    AVPacket pkt = {
        .size = buf->size,
        .data = buf->data,
        .buf = buf,
    };
    return new_demux_packet_from_avpacket(&pkt);
}