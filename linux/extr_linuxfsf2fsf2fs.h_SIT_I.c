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
struct sit_info {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ sit_info; } ;

/* Variables and functions */
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 

__attribute__((used)) static inline struct sit_info *SIT_I(struct f2fs_sb_info *sbi)
{
	return (struct sit_info *)(SM_I(sbi)->sit_info);
}