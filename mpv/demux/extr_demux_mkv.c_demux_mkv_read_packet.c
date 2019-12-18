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
struct mkv_demuxer {scalar_t__ num_packets; struct demux_packet** packets; } ;
struct demuxer {struct mkv_demuxer* priv; } ;
struct demux_packet {int dummy; } ;
struct block_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct demux_packet**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_block (struct block_info*) ; 
 int /*<<< orphan*/  handle_block (struct demuxer*,struct block_info*) ; 
 int read_next_block (struct demuxer*,struct block_info*) ; 

__attribute__((used)) static bool demux_mkv_read_packet(struct demuxer *demuxer,
                                  struct demux_packet **pkt)
{
    struct mkv_demuxer *mkv_d = demuxer->priv;

    for (;;) {
        if (mkv_d->num_packets) {
            *pkt = mkv_d->packets[0];
            MP_TARRAY_REMOVE_AT(mkv_d->packets, mkv_d->num_packets, 0);
            return true;
        }

        int res;
        struct block_info block;
        res = read_next_block(demuxer, &block);
        if (res < 0)
            return false;
        if (res > 0) {
            handle_block(demuxer, &block);
            free_block(&block);
        }
    }
}