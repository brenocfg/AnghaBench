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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct dim_stats {int dummy; } ;
struct dim_sample {scalar_t__ comp_ctr; scalar_t__ event_ctr; } ;
struct dim {int state; struct dim_sample start_sample; int /*<<< orphan*/  work; struct dim_sample measuring_sample; } ;

/* Variables and functions */
#define  DIM_APPLY_NEW_PROFILE 130 
#define  DIM_MEASURE_IN_PROGRESS 129 
 scalar_t__ DIM_NEVENTS ; 
#define  DIM_START_MEASURE 128 
 int /*<<< orphan*/  dim_calc_stats (struct dim_sample*,struct dim_sample*,struct dim_stats*) ; 
 int /*<<< orphan*/  dim_update_sample_with_comps (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct dim_sample*) ; 
 int /*<<< orphan*/  rdma_dim_decision (struct dim_stats*,struct dim*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void rdma_dim(struct dim *dim, u64 completions)
{
	struct dim_sample *curr_sample = &dim->measuring_sample;
	struct dim_stats curr_stats;
	u32 nevents;

	dim_update_sample_with_comps(curr_sample->event_ctr + 1, 0, 0,
				     curr_sample->comp_ctr + completions,
				     &dim->measuring_sample);

	switch (dim->state) {
	case DIM_MEASURE_IN_PROGRESS:
		nevents = curr_sample->event_ctr - dim->start_sample.event_ctr;
		if (nevents < DIM_NEVENTS)
			break;
		dim_calc_stats(&dim->start_sample, curr_sample, &curr_stats);
		if (rdma_dim_decision(&curr_stats, dim)) {
			dim->state = DIM_APPLY_NEW_PROFILE;
			schedule_work(&dim->work);
			break;
		}
		/* fall through */
	case DIM_START_MEASURE:
		dim->state = DIM_MEASURE_IN_PROGRESS;
		dim_update_sample_with_comps(curr_sample->event_ctr, 0, 0,
					     curr_sample->comp_ctr,
					     &dim->start_sample);
		break;
	case DIM_APPLY_NEW_PROFILE:
		break;
	}
}