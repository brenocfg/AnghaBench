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
struct tep_format_field {int offset; int flags; } ;
struct perf_sample {void* raw_data; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 int TEP_FIELD_IS_DYNAMIC ; 
 struct tep_format_field* perf_evsel__field (struct evsel*,char const*) ; 

void *perf_evsel__rawptr(struct evsel *evsel, struct perf_sample *sample,
			 const char *name)
{
	struct tep_format_field *field = perf_evsel__field(evsel, name);
	int offset;

	if (!field)
		return NULL;

	offset = field->offset;

	if (field->flags & TEP_FIELD_IS_DYNAMIC) {
		offset = *(int *)(sample->raw_data + field->offset);
		offset &= 0xffff;
	}

	return sample->raw_data + offset;
}