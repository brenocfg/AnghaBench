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
struct internal_subdev {TYPE_1__* id; } ;
struct TYPE_2__ {int index; char* name; } ;

/* Variables and functions */
 int num_isd ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static inline void isd_to_devname(char *devname, int sz,
				  const struct internal_subdev *isd,
				  int ipu_id)
{
	int pdev_id = ipu_id * num_isd + isd->id->index;

	snprintf(devname, sz, "%s.%d", isd->id->name, pdev_id);
}