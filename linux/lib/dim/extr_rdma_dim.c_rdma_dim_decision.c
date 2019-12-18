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
typedef  scalar_t__ u8 ;
struct dim_stats {int cpe_ratio; } ;
struct dim {int profile_ix; scalar_t__ tune_state; struct dim_stats prev_stats; } ;

/* Variables and functions */
 int DIM_ON_EDGE ; 
 scalar_t__ DIM_PARKING_ON_TOP ; 
 scalar_t__ DIM_PARKING_TIRED ; 
#define  DIM_STATS_BETTER 130 
#define  DIM_STATS_SAME 129 
#define  DIM_STATS_WORSE 128 
 int /*<<< orphan*/  dim_turn (struct dim*) ; 
 int rdma_dim_stats_compare (struct dim_stats*,struct dim_stats*) ; 
 int rdma_dim_step (struct dim*) ; 

__attribute__((used)) static bool rdma_dim_decision(struct dim_stats *curr_stats, struct dim *dim)
{
	int prev_ix = dim->profile_ix;
	u8 state = dim->tune_state;
	int stats_res;
	int step_res;

	if (state != DIM_PARKING_ON_TOP && state != DIM_PARKING_TIRED) {
		stats_res = rdma_dim_stats_compare(curr_stats,
						   &dim->prev_stats);

		switch (stats_res) {
		case DIM_STATS_SAME:
			if (curr_stats->cpe_ratio <= 50 * prev_ix)
				dim->profile_ix = 0;
			break;
		case DIM_STATS_WORSE:
			dim_turn(dim);
			/* fall through */
		case DIM_STATS_BETTER:
			step_res = rdma_dim_step(dim);
			if (step_res == DIM_ON_EDGE)
				dim_turn(dim);
			break;
		}
	}

	dim->prev_stats = *curr_stats;

	return dim->profile_ix != prev_ix;
}