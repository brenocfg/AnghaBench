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
struct perf_probe_point {char* function; char* offset; char* line; char* file; scalar_t__ retprobe; } ;

/* Variables and functions */
 int strbuf_addf (struct strbuf*,char*,char*) ; 
 int strbuf_addstr (struct strbuf*,char*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

char *synthesize_perf_probe_point(struct perf_probe_point *pp)
{
	struct strbuf buf;
	char *tmp, *ret = NULL;
	int len, err = 0;

	if (strbuf_init(&buf, 64) < 0)
		return NULL;

	if (pp->function) {
		if (strbuf_addstr(&buf, pp->function) < 0)
			goto out;
		if (pp->offset)
			err = strbuf_addf(&buf, "+%lu", pp->offset);
		else if (pp->line)
			err = strbuf_addf(&buf, ":%d", pp->line);
		else if (pp->retprobe)
			err = strbuf_addstr(&buf, "%return");
		if (err)
			goto out;
	}
	if (pp->file) {
		tmp = pp->file;
		len = strlen(tmp);
		if (len > 30) {
			tmp = strchr(pp->file + len - 30, '/');
			tmp = tmp ? tmp + 1 : pp->file + len - 30;
		}
		err = strbuf_addf(&buf, "@%s", tmp);
		if (!err && !pp->function && pp->line)
			err = strbuf_addf(&buf, ":%d", pp->line);
	}
	if (!err)
		ret = strbuf_detach(&buf, NULL);
out:
	strbuf_release(&buf);
	return ret;
}