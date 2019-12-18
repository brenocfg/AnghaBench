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
struct probe_cache_entry {int /*<<< orphan*/  pev; int /*<<< orphan*/  spev; int /*<<< orphan*/  tevlist; int /*<<< orphan*/  node; } ;
struct perf_probe_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ perf_probe_event__copy (int /*<<< orphan*/ *,struct perf_probe_event*) ; 
 int /*<<< orphan*/  probe_cache_entry__delete (struct probe_cache_entry*) ; 
 int /*<<< orphan*/  strlist__new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synthesize_perf_probe_command (struct perf_probe_event*) ; 
 struct probe_cache_entry* zalloc (int) ; 
 int /*<<< orphan*/  zfree (struct probe_cache_entry**) ; 

__attribute__((used)) static struct probe_cache_entry *
probe_cache_entry__new(struct perf_probe_event *pev)
{
	struct probe_cache_entry *entry = zalloc(sizeof(*entry));

	if (entry) {
		INIT_LIST_HEAD(&entry->node);
		entry->tevlist = strlist__new(NULL, NULL);
		if (!entry->tevlist)
			zfree(&entry);
		else if (pev) {
			entry->spev = synthesize_perf_probe_command(pev);
			if (!entry->spev ||
			    perf_probe_event__copy(&entry->pev, pev) < 0) {
				probe_cache_entry__delete(entry);
				return NULL;
			}
		}
	}

	return entry;
}