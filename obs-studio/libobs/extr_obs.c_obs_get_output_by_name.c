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
typedef  int /*<<< orphan*/  obs_output_t ;
struct TYPE_3__ {int /*<<< orphan*/  outputs_mutex; int /*<<< orphan*/  first_output; } ;
struct TYPE_4__ {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/ * get_context_by_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  obs_output_addref_safe_ ; 

obs_output_t *obs_get_output_by_name(const char *name)
{
	if (!obs)
		return NULL;
	return get_context_by_name(&obs->data.first_output, name,
				   &obs->data.outputs_mutex,
				   obs_output_addref_safe_);
}