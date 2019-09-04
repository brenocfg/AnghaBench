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
struct gfs2_sbd {unsigned int sd_jbsize; } ;

/* Variables and functions */
 int ERANGE ; 
 size_t GFS2_EA_MAX_DATA_LEN ; 
 int /*<<< orphan*/  ea_calc_size (struct gfs2_sbd*,unsigned int,size_t,unsigned int*) ; 

__attribute__((used)) static int ea_check_size(struct gfs2_sbd *sdp, unsigned int nsize, size_t dsize)
{
	unsigned int size;

	if (dsize > GFS2_EA_MAX_DATA_LEN)
		return -ERANGE;

	ea_calc_size(sdp, nsize, dsize, &size);

	/* This can only happen with 512 byte blocks */
	if (size > sdp->sd_jbsize)
		return -ERANGE;

	return 0;
}