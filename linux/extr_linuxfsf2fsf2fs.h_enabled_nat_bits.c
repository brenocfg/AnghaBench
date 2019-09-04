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
struct f2fs_sb_info {int dummy; } ;
struct cp_control {int reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_NAT_BITS_FLAG ; 
 int CP_UMOUNT ; 
 int is_set_ckpt_flags (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool enabled_nat_bits(struct f2fs_sb_info *sbi,
					struct cp_control *cpc)
{
	bool set = is_set_ckpt_flags(sbi, CP_NAT_BITS_FLAG);

	return (cpc) ? (cpc->reason & CP_UMOUNT) && set : set;
}