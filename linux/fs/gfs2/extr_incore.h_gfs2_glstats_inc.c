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
struct TYPE_2__ {int /*<<< orphan*/ * stats; } ;
struct gfs2_glock {TYPE_1__ gl_stats; } ;

/* Variables and functions */

__attribute__((used)) static inline void gfs2_glstats_inc(struct gfs2_glock *gl, int which)
{
	gl->gl_stats.stats[which]++;
}