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
struct perf_event_attr {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ __add_event (struct list_head*,int*,struct perf_event_attr*,char*,int /*<<< orphan*/ *,struct list_head*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_event(struct list_head *list, int *idx,
		     struct perf_event_attr *attr, char *name,
		     struct list_head *config_terms)
{
	return __add_event(list, idx, attr, name, NULL, config_terms, false, NULL) ? 0 : -ENOMEM;
}