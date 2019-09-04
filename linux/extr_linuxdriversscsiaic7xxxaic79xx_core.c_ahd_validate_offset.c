#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct ahd_softc {int bugs; } ;
struct TYPE_4__ {scalar_t__ offset; } ;
struct TYPE_3__ {scalar_t__ offset; } ;
struct ahd_initiator_tinfo {TYPE_2__ goal; TYPE_1__ user; } ;
typedef  scalar_t__ role_t ;

/* Variables and functions */
 int AHD_PACED_NEGTABLE_BUG ; 
 scalar_t__ AHD_SYNCRATE_PACED ; 
 scalar_t__ MAX_OFFSET_NON_PACED ; 
 scalar_t__ MAX_OFFSET_PACED ; 
 scalar_t__ MAX_OFFSET_PACED_BUG ; 
 scalar_t__ ROLE_TARGET ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ahd_validate_offset(struct ahd_softc *ahd,
		    struct ahd_initiator_tinfo *tinfo,
		    u_int period, u_int *offset, int wide,
		    role_t role)
{
	u_int maxoffset;

	/* Limit offset to what we can do */
	if (period == 0)
		maxoffset = 0;
	else if (period <= AHD_SYNCRATE_PACED) {
		if ((ahd->bugs & AHD_PACED_NEGTABLE_BUG) != 0)
			maxoffset = MAX_OFFSET_PACED_BUG;
		else
			maxoffset = MAX_OFFSET_PACED;
	} else
		maxoffset = MAX_OFFSET_NON_PACED;
	*offset = min(*offset, maxoffset);
	if (tinfo != NULL) {
		if (role == ROLE_TARGET)
			*offset = min(*offset, (u_int)tinfo->user.offset);
		else
			*offset = min(*offset, (u_int)tinfo->goal.offset);
	}
}