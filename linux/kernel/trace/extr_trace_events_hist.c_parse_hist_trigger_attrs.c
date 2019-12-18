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
struct trace_array {int dummy; } ;
struct hist_trigger_attrs {int pause; int cont; int clear; scalar_t__ clock; int /*<<< orphan*/  keys_str; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct hist_trigger_attrs* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  destroy_hist_trigger_attrs (struct hist_trigger_attrs*) ; 
 scalar_t__ kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct hist_trigger_attrs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int parse_action (char*,struct hist_trigger_attrs*) ; 
 int parse_assignment (struct trace_array*,char*,struct hist_trigger_attrs*) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static struct hist_trigger_attrs *
parse_hist_trigger_attrs(struct trace_array *tr, char *trigger_str)
{
	struct hist_trigger_attrs *attrs;
	int ret = 0;

	attrs = kzalloc(sizeof(*attrs), GFP_KERNEL);
	if (!attrs)
		return ERR_PTR(-ENOMEM);

	while (trigger_str) {
		char *str = strsep(&trigger_str, ":");

		if (strchr(str, '=')) {
			ret = parse_assignment(tr, str, attrs);
			if (ret)
				goto free;
		} else if (strcmp(str, "pause") == 0)
			attrs->pause = true;
		else if ((strcmp(str, "cont") == 0) ||
			 (strcmp(str, "continue") == 0))
			attrs->cont = true;
		else if (strcmp(str, "clear") == 0)
			attrs->clear = true;
		else {
			ret = parse_action(str, attrs);
			if (ret)
				goto free;
		}
	}

	if (!attrs->keys_str) {
		ret = -EINVAL;
		goto free;
	}

	if (!attrs->clock) {
		attrs->clock = kstrdup("global", GFP_KERNEL);
		if (!attrs->clock) {
			ret = -ENOMEM;
			goto free;
		}
	}

	return attrs;
 free:
	destroy_hist_trigger_attrs(attrs);

	return ERR_PTR(ret);
}