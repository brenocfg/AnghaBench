#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t num; int /*<<< orphan*/ * array; } ;
struct TYPE_5__ {TYPE_3__ roots; } ;
typedef  TYPE_1__ profiler_snapshot_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  da_free (TYPE_3__) ; 
 int /*<<< orphan*/  free_snapshot_entry (int /*<<< orphan*/ *) ; 

void profile_snapshot_free(profiler_snapshot_t *snap)
{
	if (!snap)
		return;

	for (size_t i = 0; i < snap->roots.num; i++)
		free_snapshot_entry(&snap->roots.array[i]);

	da_free(snap->roots);
	bfree(snap);
}