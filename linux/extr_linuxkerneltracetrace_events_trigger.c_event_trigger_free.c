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
struct event_trigger_data {scalar_t__ ref; } ;

/* Variables and functions */
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  trigger_data_free (struct event_trigger_data*) ; 

__attribute__((used)) static void
event_trigger_free(struct event_trigger_ops *ops,
		   struct event_trigger_data *data)
{
	if (WARN_ON_ONCE(data->ref <= 0))
		return;

	data->ref--;
	if (!data->ref)
		trigger_data_free(data);
}