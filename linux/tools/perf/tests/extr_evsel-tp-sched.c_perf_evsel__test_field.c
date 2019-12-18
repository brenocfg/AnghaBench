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
struct tep_format_field {int flags; int size; } ;
struct evsel {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int TEP_FIELD_IS_SIGNED ; 
 struct tep_format_field* perf_evsel__field (struct evsel*,char const*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char const*,...) ; 

__attribute__((used)) static int perf_evsel__test_field(struct evsel *evsel, const char *name,
				  int size, bool should_be_signed)
{
	struct tep_format_field *field = perf_evsel__field(evsel, name);
	int is_signed;
	int ret = 0;

	if (field == NULL) {
		pr_debug("%s: \"%s\" field not found!\n", evsel->name, name);
		return -1;
	}

	is_signed = !!(field->flags & TEP_FIELD_IS_SIGNED);
	if (should_be_signed && !is_signed) {
		pr_debug("%s: \"%s\" signedness(%d) is wrong, should be %d\n",
			 evsel->name, name, is_signed, should_be_signed);
		ret = -1;
	}

	if (field->size != size) {
		pr_debug("%s: \"%s\" size (%d) should be %d!\n",
			 evsel->name, name, field->size, size);
		ret = -1;
	}

	return ret;
}