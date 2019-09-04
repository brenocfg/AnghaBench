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
struct perf_hpp {int dummy; } ;
struct hist_entry {TYPE_1__* hists; } ;
struct TYPE_2__ {int /*<<< orphan*/  hpp_list; } ;

/* Variables and functions */
 int __hist_entry__snprintf (struct hist_entry*,struct perf_hpp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hist_entry__snprintf(struct hist_entry *he, struct perf_hpp *hpp)
{
	return __hist_entry__snprintf(he, hpp, he->hists->hpp_list);
}