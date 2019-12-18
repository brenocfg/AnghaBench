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
struct script_callback {int removed; int /*<<< orphan*/  (* on_remove ) (struct script_callback*) ;struct script_callback** p_prev_next; struct script_callback* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  detach_mutex ; 
 struct script_callback* detached_callbacks ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct script_callback*) ; 

__attribute__((used)) static inline void remove_script_callback(struct script_callback *cb)
{
	cb->removed = true;

	struct script_callback *next = cb->next;
	if (next)
		next->p_prev_next = cb->p_prev_next;
	*cb->p_prev_next = cb->next;

	pthread_mutex_lock(&detach_mutex);
	next = detached_callbacks;
	cb->next = next;
	if (next)
		next->p_prev_next = &cb->next;
	cb->p_prev_next = &detached_callbacks;
	detached_callbacks = cb;
	pthread_mutex_unlock(&detach_mutex);

	if (cb->on_remove)
		cb->on_remove(cb);
}