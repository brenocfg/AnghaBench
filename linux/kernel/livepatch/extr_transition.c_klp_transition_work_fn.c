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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  klp_mutex ; 
 scalar_t__ klp_transition_patch ; 
 int /*<<< orphan*/  klp_try_complete_transition () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void klp_transition_work_fn(struct work_struct *work)
{
	mutex_lock(&klp_mutex);

	if (klp_transition_patch)
		klp_try_complete_transition();

	mutex_unlock(&klp_mutex);
}