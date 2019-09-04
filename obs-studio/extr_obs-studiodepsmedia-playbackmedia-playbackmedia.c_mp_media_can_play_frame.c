#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_decode {scalar_t__ frame_pts; scalar_t__ frame_ready; } ;
struct TYPE_3__ {scalar_t__ next_pts_ns; } ;
typedef  TYPE_1__ mp_media_t ;

/* Variables and functions */

__attribute__((used)) static inline bool mp_media_can_play_frame(mp_media_t *m,
		struct mp_decode *d)
{
	return d->frame_ready && d->frame_pts <= m->next_pts_ns;
}