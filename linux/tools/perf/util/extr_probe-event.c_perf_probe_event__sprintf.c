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
struct strbuf {int dummy; } ;
struct perf_probe_event {int nargs; int /*<<< orphan*/ * args; int /*<<< orphan*/  point; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int strbuf_add (struct strbuf*,char*,int) ; 
 int strbuf_addch (struct strbuf*,char) ; 
 int strbuf_addf (struct strbuf*,char*,char const*) ; 
 int strbuf_addstr (struct strbuf*,char*) ; 
 char* synthesize_perf_probe_arg (int /*<<< orphan*/ *) ; 
 char* synthesize_perf_probe_point (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perf_probe_event__sprintf(const char *group, const char *event,
				     struct perf_probe_event *pev,
				     const char *module,
				     struct strbuf *result)
{
	int i, ret;
	char *buf;

	if (asprintf(&buf, "%s:%s", group, event) < 0)
		return -errno;
	ret = strbuf_addf(result, "  %-20s (on ", buf);
	free(buf);
	if (ret)
		return ret;

	/* Synthesize only event probe point */
	buf = synthesize_perf_probe_point(&pev->point);
	if (!buf)
		return -ENOMEM;
	ret = strbuf_addstr(result, buf);
	free(buf);

	if (!ret && module)
		ret = strbuf_addf(result, " in %s", module);

	if (!ret && pev->nargs > 0) {
		ret = strbuf_add(result, " with", 5);
		for (i = 0; !ret && i < pev->nargs; i++) {
			buf = synthesize_perf_probe_arg(&pev->args[i]);
			if (!buf)
				return -ENOMEM;
			ret = strbuf_addf(result, " %s", buf);
			free(buf);
		}
	}
	if (!ret)
		ret = strbuf_addch(result, ')');

	return ret;
}