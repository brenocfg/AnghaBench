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
struct gl_video {int fb_depth; } ;

/* Variables and functions */

void gl_video_set_fb_depth(struct gl_video *p, int fb_depth)
{
    p->fb_depth = fb_depth;
}