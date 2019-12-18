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
struct osd_state {int dummy; } ;
struct gl_video {struct osd_state* osd_state; int /*<<< orphan*/ * osd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpgl_osd_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_osd (struct gl_video*) ; 

void gl_video_set_osd_source(struct gl_video *p, struct osd_state *osd)
{
    mpgl_osd_destroy(p->osd);
    p->osd = NULL;
    p->osd_state = osd;
    reinit_osd(p);
}