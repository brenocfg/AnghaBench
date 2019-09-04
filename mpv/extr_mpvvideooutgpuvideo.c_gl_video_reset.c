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
struct gl_video {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_video_reset_surfaces (struct gl_video*) ; 

void gl_video_reset(struct gl_video *p)
{
    gl_video_reset_surfaces(p);
}