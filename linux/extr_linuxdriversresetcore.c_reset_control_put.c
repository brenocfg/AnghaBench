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
struct reset_control {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct reset_control*) ; 
 int /*<<< orphan*/  __reset_control_put_internal (struct reset_control*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_array_put (int /*<<< orphan*/ ) ; 
 scalar_t__ reset_control_is_array (struct reset_control*) ; 
 int /*<<< orphan*/  reset_list_mutex ; 
 int /*<<< orphan*/  rstc_to_array (struct reset_control*) ; 

void reset_control_put(struct reset_control *rstc)
{
	if (IS_ERR_OR_NULL(rstc))
		return;

	if (reset_control_is_array(rstc)) {
		reset_control_array_put(rstc_to_array(rstc));
		return;
	}

	mutex_lock(&reset_list_mutex);
	__reset_control_put_internal(rstc);
	mutex_unlock(&reset_list_mutex);
}