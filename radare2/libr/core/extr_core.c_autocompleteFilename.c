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
typedef  int /*<<< orphan*/  RLineCompletion ;
typedef  TYPE_1__ RLineBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  R_SYS_DIR ; 
 int /*<<< orphan*/  autocomplete_process_path (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_str_new (char*) ; 
 char* r_str_newf (char*,char*,int /*<<< orphan*/ ,char const*) ; 
 char* r_str_trim_ro (char*) ; 
 char* r_str_word_get0 (char*,int) ; 
 int r_str_word_set0 (char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void autocompleteFilename(RLineCompletion *completion, RLineBuffer *buf, char **extra_paths, int narg) {
	char *args = NULL, *input = NULL;
	int n = 0, i = 0;
	char *pipe = strchr (buf->data, '>');
	if (pipe) {
		args = r_str_new (pipe + 1);
	} else {
		args = r_str_new (buf->data);
	}
	if (!args) {
		goto out;
	}

	n = r_str_word_set0 (args);
	if (n < narg) {
		goto out;
	}

	input = r_str_new (r_str_word_get0 (args, narg));
	if (!input) {
		goto out;
	}
	const char *tinput = r_str_trim_ro (input);

	autocomplete_process_path (completion, buf->data, tinput);

	if (input[0] == '/' || input[0] == '.' || !extra_paths) {
		goto out;
	}

	for (i = 0; extra_paths[i]; i ++) {
		char *s = r_str_newf ("%s%s%s", extra_paths[i], R_SYS_DIR, tinput);
		if (!s) {
			break;
		}
		autocomplete_process_path (completion, buf->data, s);
	}
out:
	free (args);
	free (input);
}