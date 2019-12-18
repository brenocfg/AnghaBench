#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strlist {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  symbol; } ;
struct probe_trace_event {TYPE_1__ point; scalar_t__ uprobes; } ;
struct probe_cache {int dummy; } ;
struct perf_probe_event {int /*<<< orphan*/  nsi; int /*<<< orphan*/  target; scalar_t__ uprobes; } ;
struct nscookie {int dummy; } ;
struct TYPE_4__ {scalar_t__ cache; } ;

/* Variables and functions */
 int EINVAL ; 
 int __open_probe_file_and_namelist (int,struct strlist**) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  nsinfo__mountns_enter (int /*<<< orphan*/ ,struct nscookie*) ; 
 int /*<<< orphan*/  nsinfo__mountns_exit (struct nscookie*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 scalar_t__ probe_cache__add_entry (struct probe_cache*,struct perf_probe_event*,struct probe_trace_event*,int) ; 
 scalar_t__ probe_cache__commit (struct probe_cache*) ; 
 int /*<<< orphan*/  probe_cache__delete (struct probe_cache*) ; 
 struct probe_cache* probe_cache__new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ probe_conf ; 
 int probe_file__add_event (int,struct probe_trace_event*) ; 
 int probe_trace_event__set_name (struct probe_trace_event*,struct perf_probe_event*,struct strlist*,int) ; 
 int /*<<< orphan*/  strlist__delete (struct strlist*) ; 
 int /*<<< orphan*/  warn_uprobe_event_compat (struct probe_trace_event*) ; 

__attribute__((used)) static int __add_probe_trace_events(struct perf_probe_event *pev,
				     struct probe_trace_event *tevs,
				     int ntevs, bool allow_suffix)
{
	int i, fd[2] = {-1, -1}, up, ret;
	struct probe_trace_event *tev = NULL;
	struct probe_cache *cache = NULL;
	struct strlist *namelist[2] = {NULL, NULL};
	struct nscookie nsc;

	up = pev->uprobes ? 1 : 0;
	fd[up] = __open_probe_file_and_namelist(up, &namelist[up]);
	if (fd[up] < 0)
		return fd[up];

	ret = 0;
	for (i = 0; i < ntevs; i++) {
		tev = &tevs[i];
		up = tev->uprobes ? 1 : 0;
		if (fd[up] == -1) {	/* Open the kprobe/uprobe_events */
			fd[up] = __open_probe_file_and_namelist(up,
								&namelist[up]);
			if (fd[up] < 0)
				goto close_out;
		}
		/* Skip if the symbol is out of .text or blacklisted */
		if (!tev->point.symbol && !pev->uprobes)
			continue;

		/* Set new name for tev (and update namelist) */
		ret = probe_trace_event__set_name(tev, pev, namelist[up],
						  allow_suffix);
		if (ret < 0)
			break;

		nsinfo__mountns_enter(pev->nsi, &nsc);
		ret = probe_file__add_event(fd[up], tev);
		nsinfo__mountns_exit(&nsc);
		if (ret < 0)
			break;

		/*
		 * Probes after the first probe which comes from same
		 * user input are always allowed to add suffix, because
		 * there might be several addresses corresponding to
		 * one code line.
		 */
		allow_suffix = true;
	}
	if (ret == -EINVAL && pev->uprobes)
		warn_uprobe_event_compat(tev);
	if (ret == 0 && probe_conf.cache) {
		cache = probe_cache__new(pev->target, pev->nsi);
		if (!cache ||
		    probe_cache__add_entry(cache, pev, tevs, ntevs) < 0 ||
		    probe_cache__commit(cache) < 0)
			pr_warning("Failed to add event to probe cache\n");
		probe_cache__delete(cache);
	}

close_out:
	for (up = 0; up < 2; up++) {
		strlist__delete(namelist[up]);
		if (fd[up] >= 0)
			close(fd[up]);
	}
	return ret;
}