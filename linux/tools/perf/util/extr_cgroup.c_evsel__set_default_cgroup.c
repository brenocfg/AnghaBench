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
struct evsel {int /*<<< orphan*/ * cgrp; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cgroup__get (struct cgroup*) ; 

__attribute__((used)) static void evsel__set_default_cgroup(struct evsel *evsel, struct cgroup *cgroup)
{
	if (evsel->cgrp == NULL)
		evsel->cgrp = cgroup__get(cgroup);
}