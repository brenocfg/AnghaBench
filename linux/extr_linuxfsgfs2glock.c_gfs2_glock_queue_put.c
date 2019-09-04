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
struct gfs2_glock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gfs2_glock_queue_work (struct gfs2_glock*,int /*<<< orphan*/ ) ; 

void gfs2_glock_queue_put(struct gfs2_glock *gl)
{
	gfs2_glock_queue_work(gl, 0);
}