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
struct gfs2_sbd {scalar_t__ sd_lkstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct gfs2_sbd*) ; 

void free_sbd(struct gfs2_sbd *sdp)
{
	if (sdp->sd_lkstats)
		free_percpu(sdp->sd_lkstats);
	kfree(sdp);
}