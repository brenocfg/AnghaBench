#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct tracing_map_elt {int dummy; } ;
struct hist_trigger_data {int dummy; } ;
struct TYPE_6__ {TYPE_2__* track_var; } ;
struct action_data {TYPE_3__ track_data; } ;
struct TYPE_4__ {unsigned int idx; } ;
struct TYPE_5__ {TYPE_1__ var; } ;

/* Variables and functions */
 int /*<<< orphan*/  tracing_map_read_var (struct tracing_map_elt*,unsigned int) ; 

__attribute__((used)) static u64 get_track_val(struct hist_trigger_data *hist_data,
			 struct tracing_map_elt *elt,
			 struct action_data *data)
{
	unsigned int track_var_idx = data->track_data.track_var->var.idx;
	u64 track_val;

	track_val = tracing_map_read_var(elt, track_var_idx);

	return track_val;
}