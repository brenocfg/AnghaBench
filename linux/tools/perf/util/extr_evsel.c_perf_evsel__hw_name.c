#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct evsel {TYPE_2__ core; } ;

/* Variables and functions */
 int /*<<< orphan*/  __perf_evsel__hw_name (int /*<<< orphan*/ ) ; 
 int perf_evsel__add_modifiers (struct evsel*,char*,size_t) ; 
 int scnprintf (char*,size_t,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_evsel__hw_name(struct evsel *evsel, char *bf, size_t size)
{
	int r = scnprintf(bf, size, "%s", __perf_evsel__hw_name(evsel->core.attr.config));
	return r + perf_evsel__add_modifiers(evsel, bf + r, size - r);
}