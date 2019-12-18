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
struct TYPE_2__ {int /*<<< orphan*/  pos; } ;
struct demux_packet {TYPE_1__ cached_data; scalar_t__ is_cached; } ;
struct demux_internal {int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct demux_internal*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct demux_packet* demux_cache_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct demux_packet* demux_copy_packet (struct demux_packet*) ; 
 int /*<<< orphan*/  demux_packet_copy_attribs (struct demux_packet*,struct demux_packet*) ; 

__attribute__((used)) static struct demux_packet *read_packet_from_cache(struct demux_internal *in,
                                                   struct demux_packet *pkt)
{
    if (!pkt)
        return NULL;

    if (pkt->is_cached) {
        assert(in->cache);
        struct demux_packet *meta = pkt;
        pkt = demux_cache_read(in->cache, pkt->cached_data.pos);
        if (pkt) {
            demux_packet_copy_attribs(pkt, meta);
        } else {
            MP_ERR(in, "Failed to retrieve packet from cache.\n");
        }
    } else {
        // The returned packet is mutated etc. and will be owned by the user.
        pkt = demux_copy_packet(pkt);
    }

    return pkt;
}