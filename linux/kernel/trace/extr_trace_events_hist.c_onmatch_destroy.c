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
struct TYPE_2__ {int /*<<< orphan*/  event_system; int /*<<< orphan*/  event; } ;
struct action_data {TYPE_1__ match_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  action_data_destroy (struct action_data*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void onmatch_destroy(struct action_data *data)
{
	kfree(data->match_data.event);
	kfree(data->match_data.event_system);

	action_data_destroy(data);
}