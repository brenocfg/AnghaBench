#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_mutex_t ;
struct TYPE_8__ {TYPE_2__* prev_call; int /*<<< orphan*/ * entry; int /*<<< orphan*/ * mutex; } ;
typedef  TYPE_1__ profile_root_entry ;
typedef  int /*<<< orphan*/  profile_entry ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ profile_call ;

/* Variables and functions */
 int /*<<< orphan*/  free_call_context (TYPE_2__*) ; 
 TYPE_1__* get_root_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_root () ; 
 int /*<<< orphan*/  merge_call (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root_mutex ; 

__attribute__((used)) static void merge_context(profile_call *context)
{
	pthread_mutex_t *mutex = NULL;
	profile_entry *entry = NULL;
	profile_call *prev_call = NULL;

	if (!lock_root()) {
		free_call_context(context);
		return;
	}

	profile_root_entry *r_entry = get_root_entry(context->name);

	mutex = r_entry->mutex;
	entry = r_entry->entry;
	prev_call = r_entry->prev_call;

	r_entry->prev_call = context;

	pthread_mutex_lock(mutex);
	pthread_mutex_unlock(&root_mutex);

	merge_call(entry, context, prev_call);

	pthread_mutex_unlock(mutex);

	free_call_context(prev_call);
}