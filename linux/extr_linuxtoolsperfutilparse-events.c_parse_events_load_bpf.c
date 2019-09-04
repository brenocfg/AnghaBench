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
struct parse_events_state {TYPE_1__* error; } ;
struct list_head {int dummy; } ;
struct bpf_object {int dummy; } ;
typedef  int /*<<< orphan*/  errbuf ;
struct TYPE_2__ {void* str; void* help; } ;

/* Variables and functions */
 int BUFSIZ ; 
 int ENOTSUP ; 
 scalar_t__ IS_ERR (struct bpf_object*) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct bpf_object*) ; 
 struct bpf_object* bpf__prepare_load (char*,int) ; 
 int /*<<< orphan*/  bpf__strerror_prepare_load (char*,int,int,char*,int) ; 
 int /*<<< orphan*/  list_splice_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  obj_head_config ; 
 int parse_events_config_bpf (struct parse_events_state*,struct bpf_object*,int /*<<< orphan*/ *) ; 
 int parse_events_load_bpf_obj (struct parse_events_state*,struct list_head*,struct bpf_object*,struct list_head*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 
 int /*<<< orphan*/  split_bpf_config_terms (struct list_head*,int /*<<< orphan*/ *) ; 
 void* strdup (char*) ; 

int parse_events_load_bpf(struct parse_events_state *parse_state,
			  struct list_head *list,
			  char *bpf_file_name,
			  bool source,
			  struct list_head *head_config)
{
	int err;
	struct bpf_object *obj;
	LIST_HEAD(obj_head_config);

	if (head_config)
		split_bpf_config_terms(head_config, &obj_head_config);

	obj = bpf__prepare_load(bpf_file_name, source);
	if (IS_ERR(obj)) {
		char errbuf[BUFSIZ];

		err = PTR_ERR(obj);

		if (err == -ENOTSUP)
			snprintf(errbuf, sizeof(errbuf),
				 "BPF support is not compiled");
		else
			bpf__strerror_prepare_load(bpf_file_name,
						   source,
						   -err, errbuf,
						   sizeof(errbuf));

		parse_state->error->help = strdup("(add -v to see detail)");
		parse_state->error->str = strdup(errbuf);
		return err;
	}

	err = parse_events_load_bpf_obj(parse_state, list, obj, head_config);
	if (err)
		return err;
	err = parse_events_config_bpf(parse_state, obj, &obj_head_config);

	/*
	 * Caller doesn't know anything about obj_head_config,
	 * so combine them together again before returnning.
	 */
	if (head_config)
		list_splice_tail(&obj_head_config, head_config);
	return err;
}