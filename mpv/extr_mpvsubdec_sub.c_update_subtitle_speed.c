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
struct mp_subtitle_opts {int sub_fps; int sub_speed; } ;
struct dec_sub {double sub_speed; int video_fps; TYPE_1__* codec; struct mp_subtitle_opts* opts; } ;
struct TYPE_2__ {int frame_based; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct dec_sub*,char*,int,int) ; 

__attribute__((used)) static void update_subtitle_speed(struct dec_sub *sub)
{
    struct mp_subtitle_opts *opts = sub->opts;
    sub->sub_speed = 1.0;

    if (sub->video_fps > 0 && sub->codec->frame_based > 0) {
        MP_VERBOSE(sub, "Frame based format, dummy FPS: %f, video FPS: %f\n",
                   sub->codec->frame_based, sub->video_fps);
        sub->sub_speed *= sub->codec->frame_based / sub->video_fps;
    }

    if (opts->sub_fps && sub->video_fps)
        sub->sub_speed *= opts->sub_fps / sub->video_fps;

    sub->sub_speed *= opts->sub_speed;
}