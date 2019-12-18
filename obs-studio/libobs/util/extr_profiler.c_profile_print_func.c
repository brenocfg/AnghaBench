#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dstr {int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {size_t num; int /*<<< orphan*/ * array; } ;
struct TYPE_7__ {TYPE_1__ roots; } ;
typedef  TYPE_2__ profiler_snapshot_t ;
typedef  int /*<<< orphan*/  (* profile_entry_print_func ) (int /*<<< orphan*/ *,struct dstr*,struct dstr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 TYPE_2__* profile_snapshot_create () ; 
 int /*<<< orphan*/  profile_snapshot_free (TYPE_2__*) ; 

void profile_print_func(const char *intro, profile_entry_print_func print,
			profiler_snapshot_t *snap)
{
	struct dstr indent_buffer = {0};
	struct dstr output_buffer = {0};

	bool free_snapshot = !snap;
	if (!snap)
		snap = profile_snapshot_create();

	blog(LOG_INFO, "%s", intro);
	for (size_t i = 0; i < snap->roots.num; i++) {
		print(&snap->roots.array[i], &indent_buffer, &output_buffer, 0,
		      0, 0);
	}
	blog(LOG_INFO, "=================================================");

	if (free_snapshot)
		profile_snapshot_free(snap);

	dstr_free(&output_buffer);
	dstr_free(&indent_buffer);
}