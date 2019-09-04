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
struct demux_stream {scalar_t__ fw_packs; scalar_t__ fw_bytes; struct demux_packet* reader_head; } ;
struct demux_packet {struct demux_packet* next; } ;

/* Variables and functions */
 scalar_t__ demux_packet_estimate_total_size (struct demux_packet*) ; 

__attribute__((used)) static void recompute_buffers(struct demux_stream *ds)
{
    ds->fw_packs = 0;
    ds->fw_bytes = 0;

    for (struct demux_packet *dp = ds->reader_head; dp; dp = dp->next) {
        ds->fw_bytes += demux_packet_estimate_total_size(dp);
        ds->fw_packs++;
    }
}