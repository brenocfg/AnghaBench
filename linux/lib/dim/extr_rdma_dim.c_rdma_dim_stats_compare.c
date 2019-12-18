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
struct dim_stats {scalar_t__ cpms; scalar_t__ cpe_ratio; } ;

/* Variables and functions */
 int DIM_STATS_BETTER ; 
 int DIM_STATS_SAME ; 
 int DIM_STATS_WORSE ; 
 scalar_t__ IS_SIGNIFICANT_DIFF (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int rdma_dim_stats_compare(struct dim_stats *curr,
				  struct dim_stats *prev)
{
	/* first stat */
	if (!prev->cpms)
		return DIM_STATS_SAME;

	if (IS_SIGNIFICANT_DIFF(curr->cpms, prev->cpms))
		return (curr->cpms > prev->cpms) ? DIM_STATS_BETTER :
						DIM_STATS_WORSE;

	if (IS_SIGNIFICANT_DIFF(curr->cpe_ratio, prev->cpe_ratio))
		return (curr->cpe_ratio > prev->cpe_ratio) ? DIM_STATS_BETTER :
						DIM_STATS_WORSE;

	return DIM_STATS_SAME;
}