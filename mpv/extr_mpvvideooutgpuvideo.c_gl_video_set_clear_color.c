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
struct m_color {int dummy; } ;
struct gl_video {int force_clear_color; struct m_color clear_color; } ;

/* Variables and functions */

void gl_video_set_clear_color(struct gl_video *p, struct m_color c)
{
    p->force_clear_color = true;
    p->clear_color = c;
}