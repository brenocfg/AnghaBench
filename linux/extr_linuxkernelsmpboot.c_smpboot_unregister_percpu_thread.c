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
struct smp_hotplug_thread {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_online_cpus () ; 
 int /*<<< orphan*/  smpboot_destroy_threads (struct smp_hotplug_thread*) ; 
 int /*<<< orphan*/  smpboot_threads_lock ; 

void smpboot_unregister_percpu_thread(struct smp_hotplug_thread *plug_thread)
{
	get_online_cpus();
	mutex_lock(&smpboot_threads_lock);
	list_del(&plug_thread->list);
	smpboot_destroy_threads(plug_thread);
	mutex_unlock(&smpboot_threads_lock);
	put_online_cpus();
}