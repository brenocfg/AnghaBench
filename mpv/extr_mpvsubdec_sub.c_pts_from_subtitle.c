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
struct mp_subtitle_opts {double sub_delay; } ;
struct dec_sub {double sub_speed; struct mp_subtitle_opts* opts; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 

__attribute__((used)) static double pts_from_subtitle(struct dec_sub *sub, double pts)
{
    struct mp_subtitle_opts *opts = sub->opts;

    if (pts != MP_NOPTS_VALUE)
        pts = pts * sub->sub_speed + opts->sub_delay;

    return pts;
}