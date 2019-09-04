#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* frame; scalar_t__ frame_ready; } ;
struct TYPE_9__ {int eof; scalar_t__ scale_format; TYPE_7__ v; int /*<<< orphan*/  swscale; scalar_t__ has_video; TYPE_7__ a; scalar_t__ has_audio; } ;
typedef  TYPE_2__ mp_media_t ;
struct TYPE_8__ {scalar_t__ format; } ;

/* Variables and functions */
 int AVERROR_EOF ; 
 scalar_t__ closest_format (scalar_t__) ; 
 int /*<<< orphan*/  mp_decode_frame (TYPE_7__*) ; 
 int /*<<< orphan*/  mp_media_init_scaling (TYPE_2__*) ; 
 int mp_media_next_packet (TYPE_2__*) ; 
 int /*<<< orphan*/  mp_media_ready_to_start (TYPE_2__*) ; 

__attribute__((used)) static bool mp_media_prepare_frames(mp_media_t *m)
{
	while (!mp_media_ready_to_start(m)) {
		if (!m->eof) {
			int ret = mp_media_next_packet(m);
			if (ret == AVERROR_EOF)
				m->eof = true;
			else if (ret < 0)
				return false;
		}

		if (m->has_video && !mp_decode_frame(&m->v))
			return false;
		if (m->has_audio && !mp_decode_frame(&m->a))
			return false;
	}

	if (m->has_video && m->v.frame_ready && !m->swscale) {
		m->scale_format = closest_format(m->v.frame->format);
		if (m->scale_format != m->v.frame->format) {
			if (!mp_media_init_scaling(m)) {
				return false;
			}
		}
	}

	return true;
}