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
struct demux_stream {int eof; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_seek_range_on_packet (struct demux_stream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  back_demux_see_packets (struct demux_stream*) ; 
 int /*<<< orphan*/  wakeup_ds (struct demux_stream*) ; 

__attribute__((used)) static void mark_stream_eof(struct demux_stream *ds)
{
    if (!ds->eof) {
        ds->eof = true;
        adjust_seek_range_on_packet(ds, NULL);
        back_demux_see_packets(ds);
        wakeup_ds(ds);
    }
}