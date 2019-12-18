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
struct qtree_mem_dqinfo {int dqi_usable_bs; int dqi_entry_size; } ;
struct qt_disk_dqdbheader {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int qtree_dqstr_in_blk(struct qtree_mem_dqinfo *info)
{
	return (info->dqi_usable_bs - sizeof(struct qt_disk_dqdbheader))
	       / info->dqi_entry_size;
}