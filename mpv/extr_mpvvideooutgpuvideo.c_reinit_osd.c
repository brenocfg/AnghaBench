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
struct gl_video {scalar_t__ osd_state; int /*<<< orphan*/  log; int /*<<< orphan*/  ra; int /*<<< orphan*/ * osd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mpgl_osd_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mpgl_osd_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void reinit_osd(struct gl_video *p)
{
    mpgl_osd_destroy(p->osd);
    p->osd = NULL;
    if (p->osd_state)
        p->osd = mpgl_osd_init(p->ra, p->log, p->osd_state);
}