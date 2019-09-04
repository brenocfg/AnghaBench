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
struct TYPE_3__ {char* data; } ;
typedef  int /*<<< orphan*/  RLinePromptType ;
typedef  int /*<<< orphan*/  RLineCompletion ;
typedef  TYPE_1__ RLineBuffer ;

/* Variables and functions */
 char** getFilesFor (void*,char const*,int*) ; 
 int ms_argc ; 
 char const** ms_argv ; 
 int /*<<< orphan*/  r_line_completion_set (int /*<<< orphan*/ *,int,char const**) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int ms_autocomplete(RLineCompletion *completion, RLineBuffer *buf, RLinePromptType prompt_type, void *user) {
	const char *data = buf->data;
	r_line_completion_set (completion, ms_argc, ms_argv);
	if (!strncmp (data, "ls ", 3)
		|| !strncmp (data, "cd ", 3)
		|| !strncmp (data, "cat ", 4)
	 	|| !strncmp (data, "get ", 4)) {
		const char *file = strchr (data, ' ');
		if (file++) {
			//eprintf ("FILE (%s)\n", file);
			int tmp_argc = 0;
			// TODO: handle abs vs rel
			char **tmp_argv = getFilesFor (user, file, &tmp_argc);
			r_line_completion_set (completion, tmp_argc, (const char **)tmp_argv);
		}
		return true;
	}
	return false;
}