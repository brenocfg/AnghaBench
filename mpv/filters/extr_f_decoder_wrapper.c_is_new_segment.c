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
struct TYPE_2__ {scalar_t__ play_dir; } ;
struct priv {scalar_t__ start; scalar_t__ end; scalar_t__ codec; scalar_t__ packet_fed; TYPE_1__ public; } ;
struct mp_frame {scalar_t__ type; struct demux_packet* data; } ;
struct demux_packet {scalar_t__ start; scalar_t__ end; scalar_t__ codec; scalar_t__ back_restart; scalar_t__ segmented; } ;

/* Variables and functions */
 scalar_t__ MP_FRAME_PACKET ; 

__attribute__((used)) static bool is_new_segment(struct priv *p, struct mp_frame frame)
{
    if (frame.type != MP_FRAME_PACKET)
        return false;
    struct demux_packet *pkt = frame.data;
    return (pkt->segmented && (pkt->start != p->start || pkt->end != p->end ||
                               pkt->codec != p->codec)) ||
           (p->public.play_dir < 0 && pkt->back_restart && p->packet_fed);
}