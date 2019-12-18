#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hist_entry {TYPE_3__* branch_info; } ;
struct TYPE_5__ {TYPE_1__* sym; } ;
struct TYPE_6__ {TYPE_2__ to; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int HIST_FILTER__SYMBOL ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int hist_entry__sym_to_filter(struct hist_entry *he, int type,
				       const void *arg)
{
	const char *sym = arg;

	if (type != HIST_FILTER__SYMBOL)
		return -1;

	return sym && !(he->branch_info && he->branch_info->to.sym &&
		        strstr(he->branch_info->to.sym->name, sym));
}