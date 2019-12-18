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
struct super_block {int dummy; } ;
struct erofs_super_block {int /*<<< orphan*/  feature_incompat; } ;
struct TYPE_2__ {unsigned int feature_incompat; } ;

/* Variables and functions */
 unsigned int const EROFS_ALL_FEATURE_INCOMPAT ; 
 TYPE_1__* EROFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  erofs_err (struct super_block*,char*,unsigned int const) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_layout_compatibility(struct super_block *sb,
				       struct erofs_super_block *dsb)
{
	const unsigned int feature = le32_to_cpu(dsb->feature_incompat);

	EROFS_SB(sb)->feature_incompat = feature;

	/* check if current kernel meets all mandatory requirements */
	if (feature & (~EROFS_ALL_FEATURE_INCOMPAT)) {
		erofs_err(sb,
			  "unidentified incompatible feature %x, please upgrade kernel version",
			   feature & ~EROFS_ALL_FEATURE_INCOMPAT);
		return false;
	}
	return true;
}