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
struct hist_entry {TYPE_2__* branch_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  map; } ;
struct TYPE_4__ {TYPE_1__ from; } ;

/* Variables and functions */
 int _hist_entry__dso_snprintf (int /*<<< orphan*/ ,char*,size_t,unsigned int) ; 
 int repsep_snprintf (char*,size_t,char*,unsigned int,unsigned int,char*) ; 

__attribute__((used)) static int hist_entry__dso_from_snprintf(struct hist_entry *he, char *bf,
				    size_t size, unsigned int width)
{
	if (he->branch_info)
		return _hist_entry__dso_snprintf(he->branch_info->from.map,
						 bf, size, width);
	else
		return repsep_snprintf(bf, size, "%-*.*s", width, width, "N/A");
}