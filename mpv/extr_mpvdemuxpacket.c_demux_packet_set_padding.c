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
struct demux_packet {int dummy; } ;

/* Variables and functions */

int demux_packet_set_padding(struct demux_packet *dp, int start, int end)
{
#if LIBAVCODEC_VERSION_MICRO >= 100
    if (!start && !end)
        return 0;
    if (!dp->avpacket)
        return -1;
    uint8_t *p = av_packet_new_side_data(dp->avpacket, AV_PKT_DATA_SKIP_SAMPLES, 10);
    if (!p)
        return -1;

    AV_WL32(p + 0, start);
    AV_WL32(p + 4, end);
#endif
    return 0;
}