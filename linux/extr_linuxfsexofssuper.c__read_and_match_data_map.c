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
struct TYPE_4__ {void* raid_algorithm; void* mirrors_p1; void* group_depth; void* group_width; int /*<<< orphan*/  stripe_unit; } ;
struct exofs_sb_info {TYPE_2__ layout; } ;
struct TYPE_3__ {int /*<<< orphan*/  cb_raid_algorithm; int /*<<< orphan*/  cb_mirror_cnt; int /*<<< orphan*/  cb_group_depth; int /*<<< orphan*/  cb_group_width; int /*<<< orphan*/  cb_stripe_unit; } ;
struct exofs_device_table {TYPE_1__ dt_data_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_DBGMSG (char*,unsigned int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  _LLU (void*) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int ore_verify_layout (unsigned int,TYPE_2__*) ; 

__attribute__((used)) static int _read_and_match_data_map(struct exofs_sb_info *sbi, unsigned numdevs,
				    struct exofs_device_table *dt)
{
	int ret;

	sbi->layout.stripe_unit =
				le64_to_cpu(dt->dt_data_map.cb_stripe_unit);
	sbi->layout.group_width =
				le32_to_cpu(dt->dt_data_map.cb_group_width);
	sbi->layout.group_depth =
				le32_to_cpu(dt->dt_data_map.cb_group_depth);
	sbi->layout.mirrors_p1  =
				le32_to_cpu(dt->dt_data_map.cb_mirror_cnt) + 1;
	sbi->layout.raid_algorithm  =
				le32_to_cpu(dt->dt_data_map.cb_raid_algorithm);

	ret = ore_verify_layout(numdevs, &sbi->layout);

	EXOFS_DBGMSG("exofs: layout: "
		"num_comps=%u stripe_unit=0x%x group_width=%u "
		"group_depth=0x%llx mirrors_p1=%u raid_algorithm=%u\n",
		numdevs,
		sbi->layout.stripe_unit,
		sbi->layout.group_width,
		_LLU(sbi->layout.group_depth),
		sbi->layout.mirrors_p1,
		sbi->layout.raid_algorithm);
	return ret;
}