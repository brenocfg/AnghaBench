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
struct tp_field {int dummy; } ;
struct perf_evsel {int dummy; } ;
struct format_field {int dummy; } ;

/* Variables and functions */
 struct format_field* perf_evsel__field (struct perf_evsel*,char const*) ; 
 int tp_field__init_ptr (struct tp_field*,struct format_field*) ; 

__attribute__((used)) static int perf_evsel__init_tp_ptr_field(struct perf_evsel *evsel,
					 struct tp_field *field,
					 const char *name)
{
	struct format_field *format_field = perf_evsel__field(evsel, name);

	if (format_field == NULL)
		return -1;

	return tp_field__init_ptr(field, format_field);
}