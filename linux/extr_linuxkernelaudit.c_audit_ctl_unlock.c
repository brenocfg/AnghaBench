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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 TYPE_1__ audit_cmd_mutex ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void audit_ctl_unlock(void)
{
	audit_cmd_mutex.owner = NULL;
	mutex_unlock(&audit_cmd_mutex.lock);
}