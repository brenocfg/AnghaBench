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
struct swap_cluster_info {int flags; } ;

/* Variables and functions */
 int CLUSTER_FLAG_NEXT_NULL ; 

__attribute__((used)) static inline bool cluster_is_null(struct swap_cluster_info *info)
{
	return info->flags & CLUSTER_FLAG_NEXT_NULL;
}