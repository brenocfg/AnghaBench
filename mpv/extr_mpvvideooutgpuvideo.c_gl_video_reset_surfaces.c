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
struct gl_video {int output_tex_valid; scalar_t__ frames_drawn; scalar_t__ surface_now; scalar_t__ surface_idx; TYPE_1__* surfaces; } ;
struct TYPE_2__ {int /*<<< orphan*/  pts; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int SURFACES_MAX ; 

__attribute__((used)) static void gl_video_reset_surfaces(struct gl_video *p)
{
    for (int i = 0; i < SURFACES_MAX; i++) {
        p->surfaces[i].id = 0;
        p->surfaces[i].pts = MP_NOPTS_VALUE;
    }
    p->surface_idx = 0;
    p->surface_now = 0;
    p->frames_drawn = 0;
    p->output_tex_valid = false;
}