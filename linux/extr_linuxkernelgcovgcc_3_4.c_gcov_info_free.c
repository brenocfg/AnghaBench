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
struct gcov_info {struct gcov_info* filename; struct gcov_info* functions; TYPE_1__* counts; } ;
struct TYPE_2__ {int /*<<< orphan*/  values; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gcov_info*) ; 
 unsigned int num_counter_active (struct gcov_info*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void gcov_info_free(struct gcov_info *info)
{
	unsigned int active = num_counter_active(info);
	unsigned int i;

	for (i = 0; i < active ; i++)
		vfree(info->counts[i].values);
	kfree(info->functions);
	kfree(info->filename);
	kfree(info);
}