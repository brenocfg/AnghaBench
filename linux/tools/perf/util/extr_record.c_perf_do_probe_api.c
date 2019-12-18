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
struct TYPE_2__ {int /*<<< orphan*/  attr; } ;
struct evsel {TYPE_1__ core; } ;
struct evlist {int dummy; } ;
typedef  int /*<<< orphan*/  (* setup_probe_fn_t ) (struct evsel*) ;
typedef  int pid_t ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 int EAGAIN ; 
 scalar_t__ EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  evlist__delete (struct evlist*) ; 
 struct evsel* evlist__first (struct evlist*) ; 
 struct evlist* evlist__new () ; 
 scalar_t__ parse_events (struct evlist*,char const*,int /*<<< orphan*/ *) ; 
 unsigned long perf_event_open_cloexec_flag () ; 
 int sys_perf_event_open (int /*<<< orphan*/ *,int,int,int,unsigned long) ; 

__attribute__((used)) static int perf_do_probe_api(setup_probe_fn_t fn, int cpu, const char *str)
{
	struct evlist *evlist;
	struct evsel *evsel;
	unsigned long flags = perf_event_open_cloexec_flag();
	int err = -EAGAIN, fd;
	static pid_t pid = -1;

	evlist = evlist__new();
	if (!evlist)
		return -ENOMEM;

	if (parse_events(evlist, str, NULL))
		goto out_delete;

	evsel = evlist__first(evlist);

	while (1) {
		fd = sys_perf_event_open(&evsel->core.attr, pid, cpu, -1, flags);
		if (fd < 0) {
			if (pid == -1 && errno == EACCES) {
				pid = 0;
				continue;
			}
			goto out_delete;
		}
		break;
	}
	close(fd);

	fn(evsel);

	fd = sys_perf_event_open(&evsel->core.attr, pid, cpu, -1, flags);
	if (fd < 0) {
		if (errno == EINVAL)
			err = -EINVAL;
		goto out_delete;
	}
	close(fd);
	err = 0;

out_delete:
	evlist__delete(evlist);
	return err;
}