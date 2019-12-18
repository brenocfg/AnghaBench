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
typedef  int /*<<< orphan*/  u64 ;
struct perf_event_attr {int /*<<< orphan*/  config; int /*<<< orphan*/  size; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 struct list_head* malloc (int) ; 
 int parse_events_terms (struct list_head*,char const*) ; 
 int /*<<< orphan*/  parse_events_terms__delete (struct list_head*) ; 
 int perf_pmu__config_terms (struct list_head*,struct perf_event_attr*,struct list_head*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_pt_parse_terms_with_default(struct list_head *formats,
					     const char *str,
					     u64 *config)
{
	struct list_head *terms;
	struct perf_event_attr attr = { .size = 0, };
	int err;

	terms = malloc(sizeof(struct list_head));
	if (!terms)
		return -ENOMEM;

	INIT_LIST_HEAD(terms);

	err = parse_events_terms(terms, str);
	if (err)
		goto out_free;

	attr.config = *config;
	err = perf_pmu__config_terms(formats, &attr, terms, true, NULL);
	if (err)
		goto out_free;

	*config = attr.config;
out_free:
	parse_events_terms__delete(terms);
	return err;
}