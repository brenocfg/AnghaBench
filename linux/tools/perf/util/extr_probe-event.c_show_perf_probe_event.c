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
struct strbuf {char* buf; } ;
struct perf_probe_event {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int perf_probe_event__sprintf (char const*,char const*,struct perf_probe_event*,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

int show_perf_probe_event(const char *group, const char *event,
			  struct perf_probe_event *pev,
			  const char *module, bool use_stdout)
{
	struct strbuf buf = STRBUF_INIT;
	int ret;

	ret = perf_probe_event__sprintf(group, event, pev, module, &buf);
	if (ret >= 0) {
		if (use_stdout)
			printf("%s\n", buf.buf);
		else
			pr_info("%s\n", buf.buf);
	}
	strbuf_release(&buf);

	return ret;
}