#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  methodID; } ;
typedef  TYPE_1__ jvmti_line_info_t ;
typedef  scalar_t__ jvmtiError ;
typedef  int /*<<< orphan*/  jvmtiEnv ;

/* Variables and functions */
 scalar_t__ JVMTI_ERROR_NONE ; 
 scalar_t__ get_source_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static jvmtiError
fill_source_filenames(jvmtiEnv *jvmti, int nr_lines,
		      const jvmti_line_info_t * line_tab,
		      char ** file_names)
{
	int index;
	jvmtiError ret;

	for (index = 0; index < nr_lines; ++index) {
		ret = get_source_filename(jvmti, line_tab[index].methodID, &(file_names[index]));
		if (ret != JVMTI_ERROR_NONE)
			return ret;
	}

	return JVMTI_ERROR_NONE;
}