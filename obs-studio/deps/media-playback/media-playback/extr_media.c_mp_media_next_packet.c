#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct mp_decode {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ mp_media_t ;
struct TYPE_13__ {scalar_t__ size; } ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_ref (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int av_read_frame (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct mp_decode* get_packet_decoder (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  mp_decode_push_packet (struct mp_decode*,TYPE_2__*) ; 

__attribute__((used)) static int mp_media_next_packet(mp_media_t *media)
{
	AVPacket new_pkt;
	AVPacket pkt;
	av_init_packet(&pkt);
	new_pkt = pkt;

	int ret = av_read_frame(media->fmt, &pkt);
	if (ret < 0) {
		if (ret != AVERROR_EOF)
			blog(LOG_WARNING, "MP: av_read_frame failed: %s (%d)",
			     av_err2str(ret), ret);
		return ret;
	}

	struct mp_decode *d = get_packet_decoder(media, &pkt);
	if (d && pkt.size) {
		av_packet_ref(&new_pkt, &pkt);
		mp_decode_push_packet(d, &new_pkt);
	}

	av_packet_unref(&pkt);
	return ret;
}