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
struct TYPE_2__ {int sb_bsize; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int DATABUF_OFFSET ; 

__attribute__((used)) static inline unsigned int databuf_limit(struct gfs2_sbd *sdp)
{
	unsigned int limit;

	limit = (sdp->sd_sb.sb_bsize - DATABUF_OFFSET) / (2 * sizeof(__be64));
	return limit;
}