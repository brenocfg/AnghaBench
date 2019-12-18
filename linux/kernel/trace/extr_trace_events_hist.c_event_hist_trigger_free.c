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
struct hist_trigger_data {int dummy; } ;
struct event_trigger_ops {int dummy; } ;
struct event_trigger_data {scalar_t__ ref; scalar_t__ name; struct hist_trigger_data* private_data; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  del_named_trigger (struct event_trigger_data*) ; 
 int /*<<< orphan*/  destroy_hist_data (struct hist_trigger_data*) ; 
 int /*<<< orphan*/  remove_hist_vars (struct hist_trigger_data*) ; 
 int /*<<< orphan*/  trigger_data_free (struct event_trigger_data*) ; 
 int /*<<< orphan*/  unregister_field_var_hists (struct hist_trigger_data*) ; 

__attribute__((used)) static void event_hist_trigger_free(struct event_trigger_ops *ops,
				    struct event_trigger_data *data)
{
	struct hist_trigger_data *hist_data = data->private_data;

	if (WARN_ON_ONCE(data->ref <= 0))
		return;

	data->ref--;
	if (!data->ref) {
		if (data->name)
			del_named_trigger(data);

		trigger_data_free(data);

		remove_hist_vars(hist_data);

		unregister_field_var_hists(hist_data);

		destroy_hist_data(hist_data);
	}
}