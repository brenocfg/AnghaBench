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
struct qtree_mem_dqinfo {int dqi_usable_bs; int dqi_qtree_depth; } ;
typedef  unsigned int qid_t ;

/* Variables and functions */

__attribute__((used)) static int __get_index(struct qtree_mem_dqinfo *info, qid_t id, int depth)
{
	unsigned int epb = info->dqi_usable_bs >> 2;

	depth = info->dqi_qtree_depth - depth - 1;
	while (depth--)
		id /= epb;
	return id % epb;
}