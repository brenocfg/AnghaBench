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
struct perf_probe_arg_field {char* name; struct perf_probe_arg_field* next; scalar_t__ ref; } ;
struct perf_probe_arg {char* var; int /*<<< orphan*/  type; scalar_t__ name; struct perf_probe_arg_field* field; } ;

/* Variables and functions */
 int strbuf_addf (struct strbuf*,char*,char*,...) ; 
 int strbuf_addstr (struct strbuf*,char*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

char *synthesize_perf_probe_arg(struct perf_probe_arg *pa)
{
	struct perf_probe_arg_field *field = pa->field;
	struct strbuf buf;
	char *ret = NULL;
	int err;

	if (strbuf_init(&buf, 64) < 0)
		return NULL;

	if (pa->name && pa->var)
		err = strbuf_addf(&buf, "%s=%s", pa->name, pa->var);
	else
		err = strbuf_addstr(&buf, pa->name ?: pa->var);
	if (err)
		goto out;

	while (field) {
		if (field->name[0] == '[')
			err = strbuf_addstr(&buf, field->name);
		else
			err = strbuf_addf(&buf, "%s%s", field->ref ? "->" : ".",
					  field->name);
		field = field->next;
		if (err)
			goto out;
	}

	if (pa->type)
		if (strbuf_addf(&buf, ":%s", pa->type) < 0)
			goto out;

	ret = strbuf_detach(&buf, NULL);
out:
	strbuf_release(&buf);
	return ret;
}