#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dstr {int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {size_t num; int /*<<< orphan*/ * array; } ;
struct TYPE_5__ {TYPE_1__ roots; } ;
typedef  TYPE_2__ profiler_snapshot_t ;
typedef  int /*<<< orphan*/  (* dump_csv_func ) (void*,struct dstr*) ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  entry_dump_csv (struct dstr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (void*,struct dstr*),void*) ; 

__attribute__((used)) static void profiler_snapshot_dump(const profiler_snapshot_t *snap,
				   dump_csv_func func, void *data)
{
	struct dstr buffer = {0};

	dstr_init_copy(&buffer, "id,parent_id,name_id,parent_name_id,name,"
				"time_between_calls,time_delta_µs,count\n");
	func(data, &buffer);

	for (size_t i = 0; i < snap->roots.num; i++)
		entry_dump_csv(&buffer, NULL, &snap->roots.array[i], func,
			       data);

	dstr_free(&buffer);
}