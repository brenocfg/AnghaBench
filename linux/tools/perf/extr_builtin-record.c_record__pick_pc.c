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
struct record {int /*<<< orphan*/  evlist; } ;
struct perf_event_mmap_page {int dummy; } ;

/* Variables and functions */
 struct perf_event_mmap_page* perf_evlist__pick_pc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct perf_event_mmap_page *record__pick_pc(struct record *rec)
{
	const struct perf_event_mmap_page *pc;

	pc = perf_evlist__pick_pc(rec->evlist);
	if (pc)
		return pc;
	return NULL;
}