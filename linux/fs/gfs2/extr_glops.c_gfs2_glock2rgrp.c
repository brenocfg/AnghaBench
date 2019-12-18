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
struct gfs2_rgrpd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct gfs2_glock {TYPE_1__ gl_lockref; struct gfs2_rgrpd* gl_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct gfs2_rgrpd *gfs2_glock2rgrp(struct gfs2_glock *gl)
{
	struct gfs2_rgrpd *rgd;

	spin_lock(&gl->gl_lockref.lock);
	rgd = gl->gl_object;
	spin_unlock(&gl->gl_lockref.lock);

	return rgd;
}