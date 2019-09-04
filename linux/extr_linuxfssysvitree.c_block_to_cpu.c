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
typedef  int /*<<< orphan*/  sysv_zone_t ;
struct sysv_sb_info {int s_block_base; } ;

/* Variables and functions */
 int fs32_to_cpu (struct sysv_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int block_to_cpu(struct sysv_sb_info *sbi, sysv_zone_t nr)
{
	return sbi->s_block_base + fs32_to_cpu(sbi, nr);
}