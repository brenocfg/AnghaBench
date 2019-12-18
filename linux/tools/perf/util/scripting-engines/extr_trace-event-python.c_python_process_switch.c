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
typedef  union perf_event {int dummy; } perf_event ;
struct tables {int /*<<< orphan*/  dbe; scalar_t__ db_export_mode; } ;
struct perf_sample {int dummy; } ;
struct machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_export__switch (int /*<<< orphan*/ *,union perf_event*,struct perf_sample*,struct machine*) ; 
 struct tables tables_global ; 

__attribute__((used)) static void python_process_switch(union perf_event *event,
				  struct perf_sample *sample,
				  struct machine *machine)
{
	struct tables *tables = &tables_global;

	if (tables->db_export_mode)
		db_export__switch(&tables->dbe, event, sample, machine);
}