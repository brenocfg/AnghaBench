#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct tracing_map_elt {int dummy; } ;
struct hist_trigger_data {int dummy; } ;
struct TYPE_4__ {int (* check_val ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* track_var; } ;
struct action_data {TYPE_2__ track_data; } ;
struct TYPE_3__ {struct hist_trigger_data* hist_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_track_val (struct hist_trigger_data*,struct tracing_map_elt*,struct action_data*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool check_track_val(struct tracing_map_elt *elt,
			    struct action_data *data,
			    u64 var_val)
{
	struct hist_trigger_data *hist_data;
	u64 track_val;

	hist_data = data->track_data.track_var->hist_data;
	track_val = get_track_val(hist_data, elt, data);

	return data->track_data.check_val(track_val, var_val);
}