#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t num; int /*<<< orphan*/ * array; } ;
struct TYPE_9__ {TYPE_5__ roots; } ;
typedef  TYPE_2__ profiler_snapshot_t ;
struct TYPE_10__ {size_t num; TYPE_1__* array; } ;
struct TYPE_8__ {int /*<<< orphan*/ * mutex; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_entry_to_snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* bzalloc (int) ; 
 int /*<<< orphan*/  da_push_back_new (TYPE_5__) ; 
 int /*<<< orphan*/  da_reserve (TYPE_5__,size_t) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ root_entries ; 
 int /*<<< orphan*/  root_mutex ; 
 int /*<<< orphan*/  sort_snapshot_entry (int /*<<< orphan*/ *) ; 

profiler_snapshot_t *profile_snapshot_create(void)
{
	profiler_snapshot_t *snap = bzalloc(sizeof(profiler_snapshot_t));

	pthread_mutex_lock(&root_mutex);
	da_reserve(snap->roots, root_entries.num);
	for (size_t i = 0; i < root_entries.num; i++) {
		pthread_mutex_lock(root_entries.array[i].mutex);
		add_entry_to_snapshot(root_entries.array[i].entry,
				      da_push_back_new(snap->roots));
		pthread_mutex_unlock(root_entries.array[i].mutex);
	}
	pthread_mutex_unlock(&root_mutex);

	for (size_t i = 0; i < snap->roots.num; i++)
		sort_snapshot_entry(&snap->roots.array[i]);

	return snap;
}