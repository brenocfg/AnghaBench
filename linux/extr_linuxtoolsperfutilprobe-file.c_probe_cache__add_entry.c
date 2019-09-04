#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  symbol; } ;
struct probe_trace_event {TYPE_1__ point; } ;
struct probe_cache_entry {int /*<<< orphan*/  node; int /*<<< orphan*/  tevlist; } ;
struct probe_cache {int /*<<< orphan*/  entries; } ;
struct perf_probe_event {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 struct probe_cache_entry* probe_cache__find (struct probe_cache*,struct perf_probe_event*) ; 
 int /*<<< orphan*/  probe_cache_entry__delete (struct probe_cache_entry*) ; 
 struct probe_cache_entry* probe_cache_entry__new (struct perf_probe_event*) ; 
 int /*<<< orphan*/  strlist__add (int /*<<< orphan*/ ,char*) ; 
 char* synthesize_probe_trace_command (struct probe_trace_event*) ; 

int probe_cache__add_entry(struct probe_cache *pcache,
			   struct perf_probe_event *pev,
			   struct probe_trace_event *tevs, int ntevs)
{
	struct probe_cache_entry *entry = NULL;
	char *command;
	int i, ret = 0;

	if (!pcache || !pev || !tevs || ntevs <= 0) {
		ret = -EINVAL;
		goto out_err;
	}

	/* Remove old cache entry */
	entry = probe_cache__find(pcache, pev);
	if (entry) {
		list_del_init(&entry->node);
		probe_cache_entry__delete(entry);
	}

	ret = -ENOMEM;
	entry = probe_cache_entry__new(pev);
	if (!entry)
		goto out_err;

	for (i = 0; i < ntevs; i++) {
		if (!tevs[i].point.symbol)
			continue;

		command = synthesize_probe_trace_command(&tevs[i]);
		if (!command)
			goto out_err;
		strlist__add(entry->tevlist, command);
		free(command);
	}
	list_add_tail(&entry->node, &pcache->entries);
	pr_debug("Added probe cache: %d\n", ntevs);
	return 0;

out_err:
	pr_debug("Failed to add probe caches\n");
	probe_cache_entry__delete(entry);
	return ret;
}