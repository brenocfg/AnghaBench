#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mp_decode {TYPE_1__* stream; } ;
struct TYPE_7__ {struct mp_decode v; scalar_t__ has_video; struct mp_decode a; scalar_t__ has_audio; } ;
typedef  TYPE_2__ mp_media_t ;
struct TYPE_8__ {scalar_t__ stream_index; } ;
struct TYPE_6__ {scalar_t__ index; } ;
typedef  TYPE_3__ AVPacket ;

/* Variables and functions */

__attribute__((used)) static inline struct mp_decode *get_packet_decoder(mp_media_t *media,
		AVPacket *pkt)
{
	if (media->has_audio && pkt->stream_index == media->a.stream->index)
		return &media->a;
	if (media->has_video && pkt->stream_index == media->v.stream->index)
		return &media->v;

	return NULL;
}