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
struct gfs2_sbd {unsigned int sd_journals; int /*<<< orphan*/  sd_jindex_spin; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int gfs2_jindex_size(struct gfs2_sbd *sdp)
{
	unsigned int x;
	spin_lock(&sdp->sd_jindex_spin);
	x = sdp->sd_journals;
	spin_unlock(&sdp->sd_jindex_spin);
	return x;
}