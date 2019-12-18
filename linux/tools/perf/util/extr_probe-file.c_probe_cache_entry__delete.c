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
struct probe_cache_entry {int /*<<< orphan*/  spev; int /*<<< orphan*/  pev; int /*<<< orphan*/  tevlist; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  clear_perf_probe_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct probe_cache_entry*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlist__delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void probe_cache_entry__delete(struct probe_cache_entry *entry)
{
	if (entry) {
		BUG_ON(!list_empty(&entry->node));

		strlist__delete(entry->tevlist);
		clear_perf_probe_event(&entry->pev);
		zfree(&entry->spev);
		free(entry);
	}
}