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
struct swap_cluster_info {unsigned int flags; unsigned int data; } ;

/* Variables and functions */

__attribute__((used)) static inline void cluster_set_count_flag(struct swap_cluster_info *info,
					 unsigned int c, unsigned int f)
{
	info->flags = f;
	info->data = c;
}