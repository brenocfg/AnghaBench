#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  frame_ready; int /*<<< orphan*/  eof; } ;
struct TYPE_5__ {int /*<<< orphan*/  frame_ready; int /*<<< orphan*/  eof; } ;
struct TYPE_7__ {TYPE_2__ v; scalar_t__ has_video; TYPE_1__ a; scalar_t__ has_audio; } ;
typedef  TYPE_3__ mp_media_t ;

/* Variables and functions */

__attribute__((used)) static inline bool mp_media_ready_to_start(mp_media_t *m)
{
	if (m->has_audio && !m->a.eof && !m->a.frame_ready)
		return false;
	if (m->has_video && !m->v.eof && !m->v.frame_ready)
		return false;
	return true;
}