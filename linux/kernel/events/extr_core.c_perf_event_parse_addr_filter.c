#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  from; int /*<<< orphan*/ * to; } ;
typedef  TYPE_4__ substring_t ;
struct TYPE_11__ {int /*<<< orphan*/  nr_file_filters; } ;
struct TYPE_9__ {scalar_t__ exclude_kernel; } ;
struct perf_event {TYPE_3__ addr_filters; TYPE_2__* ctx; TYPE_1__ attr; } ;
struct TYPE_13__ {int /*<<< orphan*/  dentry; } ;
struct perf_addr_filter {int action; TYPE_7__ path; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct list_head {int dummy; } ;
typedef  enum perf_addr_filter_action_t { ____Placeholder_perf_addr_filter_action_t } perf_addr_filter_action_t ;
struct TYPE_14__ {int /*<<< orphan*/  i_mode; } ;
struct TYPE_10__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IF_ACT_FILTER 137 
#define  IF_ACT_START 136 
#define  IF_ACT_STOP 135 
#define  IF_SRC_FILE 134 
#define  IF_SRC_FILEADDR 133 
#define  IF_SRC_KERNEL 132 
#define  IF_SRC_KERNELADDR 131 
 int IF_STATE_ACTION ; 
 int IF_STATE_END ; 
 int IF_STATE_SOURCE ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 int MAX_OPT_ARGS ; 
#define  PERF_ADDR_FILTER_ACTION_FILTER 130 
#define  PERF_ADDR_FILTER_ACTION_START 129 
#define  PERF_ADDR_FILTER_ACTION_STOP 128 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_8__* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_filters_list (struct list_head*) ; 
 int /*<<< orphan*/  if_tokens ; 
 int kern_path (char*,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int kstrtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* match_strdup (TYPE_4__*) ; 
 int match_token (char*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 struct perf_addr_filter* perf_addr_filter_new (struct perf_event*,struct list_head*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
perf_event_parse_addr_filter(struct perf_event *event, char *fstr,
			     struct list_head *filters)
{
	struct perf_addr_filter *filter = NULL;
	char *start, *orig, *filename = NULL;
	substring_t args[MAX_OPT_ARGS];
	int state = IF_STATE_ACTION, token;
	unsigned int kernel = 0;
	int ret = -EINVAL;

	orig = fstr = kstrdup(fstr, GFP_KERNEL);
	if (!fstr)
		return -ENOMEM;

	while ((start = strsep(&fstr, " ,\n")) != NULL) {
		static const enum perf_addr_filter_action_t actions[] = {
			[IF_ACT_FILTER]	= PERF_ADDR_FILTER_ACTION_FILTER,
			[IF_ACT_START]	= PERF_ADDR_FILTER_ACTION_START,
			[IF_ACT_STOP]	= PERF_ADDR_FILTER_ACTION_STOP,
		};
		ret = -EINVAL;

		if (!*start)
			continue;

		/* filter definition begins */
		if (state == IF_STATE_ACTION) {
			filter = perf_addr_filter_new(event, filters);
			if (!filter)
				goto fail;
		}

		token = match_token(start, if_tokens, args);
		switch (token) {
		case IF_ACT_FILTER:
		case IF_ACT_START:
		case IF_ACT_STOP:
			if (state != IF_STATE_ACTION)
				goto fail;

			filter->action = actions[token];
			state = IF_STATE_SOURCE;
			break;

		case IF_SRC_KERNELADDR:
		case IF_SRC_KERNEL:
			kernel = 1;
			/* fall through */

		case IF_SRC_FILEADDR:
		case IF_SRC_FILE:
			if (state != IF_STATE_SOURCE)
				goto fail;

			*args[0].to = 0;
			ret = kstrtoul(args[0].from, 0, &filter->offset);
			if (ret)
				goto fail;

			if (token == IF_SRC_KERNEL || token == IF_SRC_FILE) {
				*args[1].to = 0;
				ret = kstrtoul(args[1].from, 0, &filter->size);
				if (ret)
					goto fail;
			}

			if (token == IF_SRC_FILE || token == IF_SRC_FILEADDR) {
				int fpos = token == IF_SRC_FILE ? 2 : 1;

				filename = match_strdup(&args[fpos]);
				if (!filename) {
					ret = -ENOMEM;
					goto fail;
				}
			}

			state = IF_STATE_END;
			break;

		default:
			goto fail;
		}

		/*
		 * Filter definition is fully parsed, validate and install it.
		 * Make sure that it doesn't contradict itself or the event's
		 * attribute.
		 */
		if (state == IF_STATE_END) {
			ret = -EINVAL;
			if (kernel && event->attr.exclude_kernel)
				goto fail;

			/*
			 * ACTION "filter" must have a non-zero length region
			 * specified.
			 */
			if (filter->action == PERF_ADDR_FILTER_ACTION_FILTER &&
			    !filter->size)
				goto fail;

			if (!kernel) {
				if (!filename)
					goto fail;

				/*
				 * For now, we only support file-based filters
				 * in per-task events; doing so for CPU-wide
				 * events requires additional context switching
				 * trickery, since same object code will be
				 * mapped at different virtual addresses in
				 * different processes.
				 */
				ret = -EOPNOTSUPP;
				if (!event->ctx->task)
					goto fail_free_name;

				/* look up the path and grab its inode */
				ret = kern_path(filename, LOOKUP_FOLLOW,
						&filter->path);
				if (ret)
					goto fail_free_name;

				kfree(filename);
				filename = NULL;

				ret = -EINVAL;
				if (!filter->path.dentry ||
				    !S_ISREG(d_inode(filter->path.dentry)
					     ->i_mode))
					goto fail;

				event->addr_filters.nr_file_filters++;
			}

			/* ready to consume more filters */
			state = IF_STATE_ACTION;
			filter = NULL;
		}
	}

	if (state != IF_STATE_ACTION)
		goto fail;

	kfree(orig);

	return 0;

fail_free_name:
	kfree(filename);
fail:
	free_filters_list(filters);
	kfree(orig);

	return ret;
}