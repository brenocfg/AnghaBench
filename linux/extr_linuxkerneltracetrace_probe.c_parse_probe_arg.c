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
struct fetch_type {int /*<<< orphan*/  name; int /*<<< orphan*/ * fetch; } ;
struct fetch_param {int /*<<< orphan*/  fn; void* data; } ;
struct deref_fetch_param {long offset; struct fetch_param orig; int /*<<< orphan*/  fetch; int /*<<< orphan*/  fetch_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 size_t FETCH_MTD_deref ; 
 size_t FETCH_MTD_file_offset ; 
 size_t FETCH_MTD_memory ; 
 size_t FETCH_MTD_reg ; 
 size_t FETCH_MTD_symbol ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* alloc_symbol_cache (char*,long) ; 
 struct fetch_type* find_fetch_type (int /*<<< orphan*/ *,struct fetch_type const*) ; 
 int /*<<< orphan*/  get_fetch_size_function (struct fetch_type const*,int /*<<< orphan*/ ,struct fetch_type const*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  kfree (struct deref_fetch_param*) ; 
 int kstrtol (char*,int /*<<< orphan*/ ,long*) ; 
 int kstrtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct deref_fetch_param* kzalloc (int,int /*<<< orphan*/ ) ; 
 int parse_probe_vars (char*,struct fetch_type const*,struct fetch_param*,int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int regs_query_register_offset (char*) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 
 int traceprobe_split_symbol_offset (char*,long*) ; 

__attribute__((used)) static int parse_probe_arg(char *arg, const struct fetch_type *t,
		     struct fetch_param *f, bool is_return, bool is_kprobe,
		     const struct fetch_type *ftbl)
{
	unsigned long param;
	long offset;
	char *tmp;
	int ret = 0;

	switch (arg[0]) {
	case '$':
		ret = parse_probe_vars(arg + 1, t, f, is_return, is_kprobe);
		break;

	case '%':	/* named register */
		ret = regs_query_register_offset(arg + 1);
		if (ret >= 0) {
			f->fn = t->fetch[FETCH_MTD_reg];
			f->data = (void *)(unsigned long)ret;
			ret = 0;
		}
		break;

	case '@':	/* memory, file-offset or symbol */
		if (isdigit(arg[1])) {
			ret = kstrtoul(arg + 1, 0, &param);
			if (ret)
				break;

			f->fn = t->fetch[FETCH_MTD_memory];
			f->data = (void *)param;
		} else if (arg[1] == '+') {
			/* kprobes don't support file offsets */
			if (is_kprobe)
				return -EINVAL;

			ret = kstrtol(arg + 2, 0, &offset);
			if (ret)
				break;

			f->fn = t->fetch[FETCH_MTD_file_offset];
			f->data = (void *)offset;
		} else {
			/* uprobes don't support symbols */
			if (!is_kprobe)
				return -EINVAL;

			ret = traceprobe_split_symbol_offset(arg + 1, &offset);
			if (ret)
				break;

			f->data = alloc_symbol_cache(arg + 1, offset);
			if (f->data)
				f->fn = t->fetch[FETCH_MTD_symbol];
		}
		break;

	case '+':	/* deref memory */
		arg++;	/* Skip '+', because kstrtol() rejects it. */
	case '-':
		tmp = strchr(arg, '(');
		if (!tmp)
			break;

		*tmp = '\0';
		ret = kstrtol(arg, 0, &offset);

		if (ret)
			break;

		arg = tmp + 1;
		tmp = strrchr(arg, ')');

		if (tmp) {
			struct deref_fetch_param	*dprm;
			const struct fetch_type		*t2;

			t2 = find_fetch_type(NULL, ftbl);
			*tmp = '\0';
			dprm = kzalloc(sizeof(struct deref_fetch_param), GFP_KERNEL);

			if (!dprm)
				return -ENOMEM;

			dprm->offset = offset;
			dprm->fetch = t->fetch[FETCH_MTD_memory];
			dprm->fetch_size = get_fetch_size_function(t,
							dprm->fetch, ftbl);
			ret = parse_probe_arg(arg, t2, &dprm->orig, is_return,
							is_kprobe, ftbl);
			if (ret)
				kfree(dprm);
			else {
				f->fn = t->fetch[FETCH_MTD_deref];
				f->data = (void *)dprm;
			}
		}
		break;
	}
	if (!ret && !f->fn) {	/* Parsed, but do not find fetch method */
		pr_info("%s type has no corresponding fetch method.\n", t->name);
		ret = -EINVAL;
	}

	return ret;
}