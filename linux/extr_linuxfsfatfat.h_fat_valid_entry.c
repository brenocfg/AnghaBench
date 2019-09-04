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
struct msdos_sb_info {int max_cluster; } ;

/* Variables and functions */
 int FAT_START_ENT ; 

__attribute__((used)) static inline bool fat_valid_entry(struct msdos_sb_info *sbi, int entry)
{
	return FAT_START_ENT <= entry && entry < sbi->max_cluster;
}