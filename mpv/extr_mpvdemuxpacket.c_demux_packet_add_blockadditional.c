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
typedef  int /*<<< orphan*/  uint64_t ;
struct demux_packet {int dummy; } ;

/* Variables and functions */

int demux_packet_add_blockadditional(struct demux_packet *dp, uint64_t id,
                                     void *data, size_t size)
{
#if LIBAVCODEC_VERSION_MICRO >= 100
    if (!dp->avpacket)
        return -1;
    uint8_t *sd =  av_packet_new_side_data(dp->avpacket,
                                           AV_PKT_DATA_MATROSKA_BLOCKADDITIONAL,
                                           8 + size);
    if (!sd)
        return -1;
    AV_WB64(sd, id);
    if (size > 0)
        memcpy(sd + 8, data, size);
#endif
    return 0;
}