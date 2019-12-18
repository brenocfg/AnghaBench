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
typedef  scalar_t__ uint64_t ;
struct demux_stream {TYPE_2__* reader_head; TYPE_1__* queue; } ;
struct TYPE_4__ {scalar_t__ cum_pos; } ;
struct TYPE_3__ {scalar_t__ tail_cum_pos; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t get_foward_buffered_bytes(struct demux_stream *ds)
{
    if (!ds->reader_head)
        return 0;
    return ds->queue->tail_cum_pos - ds->reader_head->cum_pos;
}