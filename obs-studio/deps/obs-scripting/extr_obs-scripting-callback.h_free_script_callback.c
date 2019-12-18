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
struct script_callback {struct script_callback* next; struct script_callback** p_prev_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  detach_mutex ; 
 int /*<<< orphan*/  just_free_script_callback (struct script_callback*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void free_script_callback(struct script_callback *cb)
{
	pthread_mutex_lock(&detach_mutex);
	struct script_callback *next = cb->next;
	if (next)
		next->p_prev_next = cb->p_prev_next;
	*cb->p_prev_next = cb->next;
	pthread_mutex_unlock(&detach_mutex);

	just_free_script_callback(cb);
}