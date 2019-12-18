#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct track_data {struct hist_trigger_data* hist_data; } ;
struct trace_event_file {int /*<<< orphan*/  tr; } ;
struct hist_trigger_data {struct trace_event_file* event_file; } ;
struct TYPE_2__ {int /*<<< orphan*/  var_str; int /*<<< orphan*/  track_var; } ;
struct action_data {scalar_t__ action; TYPE_1__ track_data; } ;

/* Variables and functions */
 scalar_t__ ACTION_SNAPSHOT ; 
 int /*<<< orphan*/  action_data_destroy (struct action_data*) ; 
 int /*<<< orphan*/  destroy_hist_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct track_data* tracing_cond_snapshot_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracing_snapshot_cond_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  track_data_free (struct track_data*) ; 

__attribute__((used)) static void track_data_destroy(struct hist_trigger_data *hist_data,
			       struct action_data *data)
{
	struct trace_event_file *file = hist_data->event_file;

	destroy_hist_field(data->track_data.track_var, 0);

	if (data->action == ACTION_SNAPSHOT) {
		struct track_data *track_data;

		track_data = tracing_cond_snapshot_data(file->tr);
		if (track_data && track_data->hist_data == hist_data) {
			tracing_snapshot_cond_disable(file->tr);
			track_data_free(track_data);
		}
	}

	kfree(data->track_data.var_str);

	action_data_destroy(data);
}