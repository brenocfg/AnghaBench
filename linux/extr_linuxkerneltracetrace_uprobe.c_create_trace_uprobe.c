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
struct path {int /*<<< orphan*/  dentry; } ;
struct trace_uprobe {unsigned long offset; TYPE_1__ tp; void* filename; struct path path; } ;
struct probe_arg {void* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct trace_uprobe*) ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 int MAX_EVENT_NAME_LEN ; 
 int MAX_TRACE_ARGS ; 
 int PTR_ERR (struct trace_uprobe*) ; 
 char* UPROBE_EVENT_SYSTEM ; 
 struct trace_uprobe* alloc_trace_uprobe (char*,char*,int,int) ; 
 int /*<<< orphan*/  d_is_reg (int /*<<< orphan*/ ) ; 
 struct trace_uprobe* find_probe_event (char*,char*) ; 
 int /*<<< orphan*/  free_trace_uprobe (struct trace_uprobe*) ; 
 int /*<<< orphan*/  is_good_name (void*) ; 
 char* kbasename (char*) ; 
 int kern_path (char*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 void* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int kstrtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int register_trace_uprobe (struct trace_uprobe*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 char* strpbrk (char*,char*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ traceprobe_conflict_field_name (void*,struct probe_arg*,int) ; 
 int traceprobe_parse_probe_arg (char*,int /*<<< orphan*/ *,struct probe_arg*,int,int,int /*<<< orphan*/ ) ; 
 int unregister_trace_uprobe (struct trace_uprobe*) ; 
 int /*<<< orphan*/  uprobe_lock ; 
 int /*<<< orphan*/  uprobes_fetch_type_table ; 

__attribute__((used)) static int create_trace_uprobe(int argc, char **argv)
{
	struct trace_uprobe *tu;
	char *arg, *event, *group, *filename;
	char buf[MAX_EVENT_NAME_LEN];
	struct path path;
	unsigned long offset;
	bool is_delete, is_return;
	int i, ret;

	ret = 0;
	is_delete = false;
	is_return = false;
	event = NULL;
	group = NULL;

	/* argc must be >= 1 */
	if (argv[0][0] == '-')
		is_delete = true;
	else if (argv[0][0] == 'r')
		is_return = true;
	else if (argv[0][0] != 'p') {
		pr_info("Probe definition must be started with 'p', 'r' or '-'.\n");
		return -EINVAL;
	}

	if (argv[0][1] == ':') {
		event = &argv[0][2];
		arg = strchr(event, '/');

		if (arg) {
			group = event;
			event = arg + 1;
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
		group = UPROBE_EVENT_SYSTEM;

	if (is_delete) {
		int ret;

		if (!event) {
			pr_info("Delete command needs an event name.\n");
			return -EINVAL;
		}
		mutex_lock(&uprobe_lock);
		tu = find_probe_event(event, group);

		if (!tu) {
			mutex_unlock(&uprobe_lock);
			pr_info("Event %s/%s doesn't exist.\n", group, event);
			return -ENOENT;
		}
		/* delete an event */
		ret = unregister_trace_uprobe(tu);
		mutex_unlock(&uprobe_lock);
		return ret;
	}

	if (argc < 2) {
		pr_info("Probe point is not specified.\n");
		return -EINVAL;
	}
	/* Find the last occurrence, in case the path contains ':' too. */
	arg = strrchr(argv[1], ':');
	if (!arg)
		return -EINVAL;

	*arg++ = '\0';
	filename = argv[1];
	ret = kern_path(filename, LOOKUP_FOLLOW, &path);
	if (ret)
		return ret;

	if (!d_is_reg(path.dentry)) {
		ret = -EINVAL;
		goto fail_address_parse;
	}

	ret = kstrtoul(arg, 0, &offset);
	if (ret)
		goto fail_address_parse;

	argc -= 2;
	argv += 2;

	/* setup a probe */
	if (!event) {
		char *tail;
		char *ptr;

		tail = kstrdup(kbasename(filename), GFP_KERNEL);
		if (!tail) {
			ret = -ENOMEM;
			goto fail_address_parse;
		}

		ptr = strpbrk(tail, ".-_");
		if (ptr)
			*ptr = '\0';

		snprintf(buf, MAX_EVENT_NAME_LEN, "%c_%s_0x%lx", 'p', tail, offset);
		event = buf;
		kfree(tail);
	}

	tu = alloc_trace_uprobe(group, event, argc, is_return);
	if (IS_ERR(tu)) {
		pr_info("Failed to allocate trace_uprobe.(%d)\n", (int)PTR_ERR(tu));
		ret = PTR_ERR(tu);
		goto fail_address_parse;
	}
	tu->offset = offset;
	tu->path = path;
	tu->filename = kstrdup(filename, GFP_KERNEL);

	if (!tu->filename) {
		pr_info("Failed to allocate filename.\n");
		ret = -ENOMEM;
		goto error;
	}

	/* parse arguments */
	ret = 0;
	for (i = 0; i < argc && i < MAX_TRACE_ARGS; i++) {
		struct probe_arg *parg = &tu->tp.args[i];

		/* Increment count for freeing args in error case */
		tu->tp.nr_args++;

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
			pr_info("Invalid argument[%d] name: %s\n", i, parg->name);
			ret = -EINVAL;
			goto error;
		}

		if (traceprobe_conflict_field_name(parg->name, tu->tp.args, i)) {
			pr_info("Argument[%d] name '%s' conflicts with "
				"another field.\n", i, argv[i]);
			ret = -EINVAL;
			goto error;
		}

		/* Parse fetch argument */
		ret = traceprobe_parse_probe_arg(arg, &tu->tp.size, parg,
						 is_return, false,
						 uprobes_fetch_type_table);
		if (ret) {
			pr_info("Parse error at argument[%d]. (%d)\n", i, ret);
			goto error;
		}
	}

	ret = register_trace_uprobe(tu);
	if (ret)
		goto error;
	return 0;

error:
	free_trace_uprobe(tu);
	return ret;

fail_address_parse:
	path_put(&path);

	pr_info("Failed to parse address or file.\n");

	return ret;
}