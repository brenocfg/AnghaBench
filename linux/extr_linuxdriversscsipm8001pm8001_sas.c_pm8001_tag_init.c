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
struct pm8001_hba_info {int tags_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm8001_tag_free (struct pm8001_hba_info*,int) ; 

void pm8001_tag_init(struct pm8001_hba_info *pm8001_ha)
{
	int i;
	for (i = 0; i < pm8001_ha->tags_num; ++i)
		pm8001_tag_free(pm8001_ha, i);
}