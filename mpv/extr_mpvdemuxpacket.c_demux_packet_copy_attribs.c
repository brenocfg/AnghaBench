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
struct demux_packet {int /*<<< orphan*/  metadata; int /*<<< orphan*/  stream; int /*<<< orphan*/  keyframe; int /*<<< orphan*/  codec; int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/  segmented; int /*<<< orphan*/  pos; int /*<<< orphan*/  duration; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_packet_tags_setref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void demux_packet_copy_attribs(struct demux_packet *dst, struct demux_packet *src)
{
    dst->pts = src->pts;
    dst->dts = src->dts;
    dst->duration = src->duration;
    dst->pos = src->pos;
    dst->segmented = src->segmented;
    dst->start = src->start;
    dst->end = src->end;
    dst->codec = src->codec;
    dst->keyframe = src->keyframe;
    dst->stream = src->stream;
    mp_packet_tags_setref(&dst->metadata, src->metadata);
}