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
struct gfs2_sbd {scalar_t__ sd_jindex; scalar_t__ sd_rindex; } ;
struct TYPE_2__ {struct gfs2_sbd* ln_sbd; } ;
struct gfs2_glock {scalar_t__ gl_object; TYPE_1__ gl_name; } ;

/* Variables and functions */

__attribute__((used)) static int inode_go_demote_ok(const struct gfs2_glock *gl)
{
	struct gfs2_sbd *sdp = gl->gl_name.ln_sbd;

	if (sdp->sd_jindex == gl->gl_object || sdp->sd_rindex == gl->gl_object)
		return 0;

	return 1;
}