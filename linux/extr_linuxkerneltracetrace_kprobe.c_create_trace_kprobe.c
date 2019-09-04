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
struct TYPE_2__ {int /*<<< orphan*/  size; struct probe_arg* args; int /*<<< orphan*/  nr_args; } ;
struct trace_kprobe {TYPE_1__ tp; } ;
struct probe_arg {int name; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct trace_kprobe*) ; 
 char* KPROBE_EVENT_SYSTEM ; 
 int KRETPROBE_MAXACTIVE_MAX ; 
 int MAX_EVENT_NAME_LEN ; 
 int MAX_TRACE_ARGS ; 
 int PTR_ERR (struct trace_kprobe*) ; 
 long UINT_MAX ; 
 struct trace_kprobe* alloc_trace_kprobe (char*,char*,void*,char*,long,int,int,int) ; 
 struct trace_kprobe* find_trace_kprobe (char*,char*) ; 
 int /*<<< orphan*/  free_trace_kprobe (struct trace_kprobe*) ; 
 int /*<<< orphan*/  is_good_name (int) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  kprobe_on_func_entry (int /*<<< orphan*/ *,char*,long) ; 
 int /*<<< orphan*/  kprobes_fetch_type_table ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int kstrtouint (char*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ kstrtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  probe_lock ; 
 int register_trace_kprobe (struct trace_kprobe*) ; 
 int /*<<< orphan*/  sanitize_event_name (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ traceprobe_conflict_field_name (int,struct probe_arg*,int) ; 
 int traceprobe_parse_probe_arg (char*,int /*<<< orphan*/ *,struct probe_arg*,int,int,int /*<<< orphan*/ ) ; 
 int traceprobe_split_symbol_offset (char*,long*) ; 
 int unregister_trace_kprobe (struct trace_kprobe*) ; 

__attribute__((used)) static int create_trace_kprobe(int argc, char **argv)
{
	/*
	 * Argument syntax:
	 *  - Add kprobe:
	 *      p[:[GRP/]EVENT] [MOD:]KSYM[+OFFS]|KADDR [FETCHARGS]
	 *  - Add kretprobe:
	 *      r[MAXACTIVE][:[GRP/]EVENT] [MOD:]KSYM[+0] [FETCHARGS]
	 * Fetch args:
	 *  $retval	: fetch return value
	 *  $stack	: fetch stack address
	 *  $stackN	: fetch Nth of stack (N:0-)
	 *  $comm       : fetch current task comm
	 *  @ADDR	: fetch memory at ADDR (ADDR should be in kernel)
	 *  @SYM[+|-offs] : fetch memory at SYM +|- offs (SYM is a data symbol)
	 *  %REG	: fetch register REG
	 * Dereferencing memory fetch:
	 *  +|-offs(ARG) : fetch memory at ARG +|- offs address.
	 * Alias name of args:
	 *  NAME=FETCHARG : set NAME as alias of FETCHARG.
	 * Type of args:
	 *  FETCHARG:TYPE : use TYPE instead of unsigned long.
	 */
	struct trace_kprobe *tk;
	int i, ret = 0;
	bool is_return = false, is_delete = false;
	char *symbol = NULL, *event = NULL, *group = NULL;
	int maxactive = 0;
	char *arg;
	long offset = 0;
	void *addr = NULL;
	char buf[MAX_EVENT_NAME_LEN];

	/* argc must be >= 1 */
	if (argv[0][0] == 'p')
		is_return = false;
	else if (argv[0][0] == 'r')
		is_return = true;
	else if (argv[0][0] == '-')
		is_delete = true;
	else {
		pr_info("Probe definition must be started with 'p', 'r' or"
			" '-'.\n");
		return -EINVAL;
	}

	event = strchr(&argv[0][1], ':');
	if (event) {
		event[0] = '\0';
		event++;
	}
	if (is_return && isdigit(argv[0][1])) {
		ret = kstrtouint(&argv[0][1], 0, &maxactive);
		if (ret) {
			pr_info("Failed to parse maxactive.\n");
			return ret;
		}
		/* kretprobes instances are iterated over via a list. The
		 * maximum should stay reasonable.
		 */
		if (maxactive > KRETPROBE_MAXACTIVE_MAX) {
			pr_info("Maxactive is too big (%d > %d).\n",
				maxactive, KRETPROBE_MAXACTIVE_MAX);
			return -E2BIG;
		}
	}

	if (event) {
		if (strchr(event, '/')) {
			group = event;
			event = strchr(group, '/') + 1;
			event[-1] = '\0';
			if (strlen(group) == 0) {
				pr_info("Group name is not specified\n");
				return -EINVAL;
			}
		}
		if (strlen(event) == 0) {
			pr_info("Event name is not specified\n");
			return -EINVAL;
		}
	}
	if (!group)
		group = KPROBE_EVENT_SYSTEM;

	if (is_delete) {
		if (!event) {
			pr_info("Delete command needs an event name.\n");
			return -EINVAL;
		}
		mutex_lock(&probe_lock);
		tk = find_trace_kprobe(event, group);
		if (!tk) {
			mutex_unlock(&probe_lock);
			pr_info("Event %s/%s doesn't exist.\n", group, event);
			return -ENOENT;
		}
		/* delete an event */
		ret = unregister_trace_kprobe(tk);
		if (ret == 0)
			free_trace_kprobe(tk);
		mutex_unlock(&probe_lock);
		return ret;
	}

	if (argc < 2) {
		pr_info("Probe point is not specified.\n");
		return -EINVAL;
	}

	/* try to parse an address. if that fails, try to read the
	 * input as a symbol. */
	if (kstrtoul(argv[1], 0, (unsigned long *)&addr)) {
		/* a symbol specified */
		symbol = argv[1];
		/* TODO: support .init module functions */
		ret = traceprobe_split_symbol_offset(symbol, &offset);
		if (ret || offset < 0 || offset > UINT_MAX) {
			pr_info("Failed to parse either an address or a symbol.\n");
			return ret;
		}
		if (offset && is_return &&
		    !kprobe_on_func_entry(NULL, symbol, offset)) {
			pr_info("Given offset is not valid for return probe.\n");
			return -EINVAL;
		}
	}
	argc -= 2; argv += 2;

	/* setup a probe */
	if (!event) {
		/* Make a new event name */
		if (symbol)
			snprintf(buf, MAX_EVENT_NAME_LEN, "%c_%s_%ld",
				 is_return ? 'r' : 'p', symbol, offset);
		else
			snprintf(buf, MAX_EVENT_NAME_LEN, "%c_0x%p",
				 is_return ? 'r' : 'p', addr);
		sanitize_event_name(buf);
		event = buf;
	}
	tk = alloc_trace_kprobe(group, event, addr, symbol, offset, maxactive,
			       argc, is_return);
	if (IS_ERR(tk)) {
		pr_info("Failed to allocate trace_probe.(%d)\n",
			(int)PTR_ERR(tk));
		return PTR_ERR(tk);
	}

	/* parse arguments */
	ret = 0;
	for (i = 0; i < argc && i < MAX_TRACE_ARGS; i++) {
		struct probe_arg *parg = &tk->tp.args[i];

		/* Increment count for freeing args in error case */
		tk->tp.nr_args++;

		/* Parse argument name */
		arg = strchr(argv[i], '=');
		if (arg) {
			*arg++ = '\0';
			parg->name = kstrdup(argv[i], GFP_KERNEL);
		} else {
			arg = argv[i];
			/* If argument name is omitted, set "argN" */
			snprintf(buf, MAX_EVENT_NAME_LEN, "arg%d", i + 1);
			parg->name = kstrdup(buf, GFP_KERNEL);
		}

		if (!parg->name) {
			pr_info("Failed to allocate argument[%d] name.\n", i);
			ret = -ENOMEM;
			goto error;
		}

		if (!is_good_name(parg->name)) {
			pr_info("Invalid argument[%d] name: %s\n",
				i, parg->name);
			ret = -EINVAL;
			goto error;
		}

		if (traceprobe_conflict_field_name(parg->name,
							tk->tp.args, i)) {
			pr_info("Argument[%d] name '%s' conflicts with "
				"another field.\n", i, argv[i]);
			ret = -EINVAL;
			goto error;
		}

		/* Parse fetch argument */
		ret = traceprobe_parse_probe_arg(arg, &tk->tp.size, parg,
						is_return, true,
						kprobes_fetch_type_table);
		if (ret) {
			pr_info("Parse error at argument[%d]. (%d)\n", i, ret);
			goto error;
		}
	}

	ret = register_trace_kprobe(tk);
	if (ret)
		goto error;
	return 0;

error:
	free_trace_kprobe(tk);
	return ret;
}