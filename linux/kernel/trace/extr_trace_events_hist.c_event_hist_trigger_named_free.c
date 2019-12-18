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
struct event_trigger_ops {int dummy; } ;
struct event_trigger_data {scalar_t__ ref; int /*<<< orphan*/  named_data; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  del_named_trigger (struct event_trigger_data*) ; 
 int /*<<< orphan*/  event_hist_trigger_free (struct event_trigger_ops*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trigger_data_free (struct event_trigger_data*) ; 

__attribute__((used)) static void event_hist_trigger_named_free(struct event_trigger_ops *ops,
					  struct event_trigger_data *data)
{
	if (WARN_ON_ONCE(data->ref <= 0))
		return;

	event_hist_trigger_free(ops, data->named_data);

	data->ref--;
	if (!data->ref) {
		del_named_trigger(data);
		trigger_data_free(data);
	}
}