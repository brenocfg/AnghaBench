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
struct TYPE_2__ {scalar_t__ fmr_physical; } ;
struct ext4_getfsmap_info {TYPE_1__ gfi_low; } ;
struct ext4_fsmap {scalar_t__ fmr_physical; } ;

/* Variables and functions */

__attribute__((used)) static bool ext4_getfsmap_rec_before_low_key(struct ext4_getfsmap_info *info,
					     struct ext4_fsmap *rec)
{
	return rec->fmr_physical < info->gfi_low.fmr_physical;
}