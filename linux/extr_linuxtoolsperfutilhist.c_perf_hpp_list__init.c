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
struct perf_hpp_list {int /*<<< orphan*/  sorts; int /*<<< orphan*/  fields; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void perf_hpp_list__init(struct perf_hpp_list *list)
{
	INIT_LIST_HEAD(&list->fields);
	INIT_LIST_HEAD(&list->sorts);
}