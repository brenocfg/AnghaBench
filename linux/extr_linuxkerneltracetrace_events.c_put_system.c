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
struct trace_subsystem_dir {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __put_system_dir (struct trace_subsystem_dir*) ; 
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_system(struct trace_subsystem_dir *dir)
{
	mutex_lock(&event_mutex);
	__put_system_dir(dir);
	mutex_unlock(&event_mutex);
}