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
struct sd_header {size_t data_len; scalar_t__ num_sd; int len; int /*<<< orphan*/  av_type; int /*<<< orphan*/  av_flags; } ;
typedef  struct sd_header uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct pkt_header {size_t data_len; scalar_t__ num_sd; int len; int /*<<< orphan*/  av_type; int /*<<< orphan*/  av_flags; } ;
struct demux_packet {int len; TYPE_1__* avpacket; struct sd_header* buffer; } ;
struct demux_cache {int dummy; } ;
typedef  int /*<<< orphan*/  sd_hd ;
typedef  int /*<<< orphan*/  hd ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int INT_MAX ; 
 struct sd_header* av_packet_new_side_data (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_seek (struct demux_cache*,int /*<<< orphan*/ ) ; 
 struct demux_packet* new_demux_packet (size_t) ; 
 int /*<<< orphan*/  read_raw (struct demux_cache*,struct sd_header*,int) ; 
 int /*<<< orphan*/  talloc_free (struct demux_packet*) ; 

struct demux_packet *demux_cache_read(struct demux_cache *cache, uint64_t pos)
{
    if (!do_seek(cache, pos))
        return NULL;

    struct pkt_header hd;

    if (!read_raw(cache, &hd, sizeof(hd)))
        return NULL;

    if (hd.data_len >= (size_t)-1)
        return NULL;

    struct demux_packet *dp = new_demux_packet(hd.data_len);
    if (!dp)
        goto fail;

    if (!read_raw(cache, dp->buffer, dp->len))
        goto fail;

    dp->avpacket->flags = hd.av_flags;

    for (uint32_t n = 0; n < hd.num_sd; n++) {
        struct sd_header sd_hd;

        if (!read_raw(cache, &sd_hd, sizeof(sd_hd)))
            goto fail;

        if (sd_hd.len > INT_MAX)
            goto fail;

        uint8_t *sd = av_packet_new_side_data(dp->avpacket, sd_hd.av_type,
                                              sd_hd.len);
        if (!sd)
            goto fail;

        if (!read_raw(cache, sd, sd_hd.len))
            goto fail;
    }

    return dp;

fail:
    talloc_free(dp);
    return NULL;
}