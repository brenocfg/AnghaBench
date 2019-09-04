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
typedef  scalar_t__ u32 ;
struct internal_subdev {TYPE_1__* id; } ;
typedef  enum isd_enum { ____Placeholder_isd_enum } isd_enum ;
struct TYPE_2__ {scalar_t__ grp_id; } ;

/* Variables and functions */
 struct internal_subdev* int_subdev ; 
 int num_isd ; 

__attribute__((used)) static const struct internal_subdev *find_intsd_by_grp_id(u32 grp_id)
{
	enum isd_enum i;

	for (i = 0; i < num_isd; i++) {
		const struct internal_subdev *isd = &int_subdev[i];

		if (isd->id->grp_id == grp_id)
			return isd;
	}

	return NULL;
}