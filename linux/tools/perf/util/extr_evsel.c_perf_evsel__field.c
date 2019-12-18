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
struct tep_format_field {int dummy; } ;
struct evsel {int /*<<< orphan*/  tp_format; } ;

/* Variables and functions */
 struct tep_format_field* tep_find_field (int /*<<< orphan*/ ,char const*) ; 

struct tep_format_field *perf_evsel__field(struct evsel *evsel, const char *name)
{
	return tep_find_field(evsel->tp_format, name);
}