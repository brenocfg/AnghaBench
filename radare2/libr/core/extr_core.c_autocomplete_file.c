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
typedef  int /*<<< orphan*/  RLineCompletion ;

/* Variables and functions */
 int /*<<< orphan*/  autocomplete_process_path (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  r_return_if_fail (char const*) ; 
 char* r_str_trim_ro (char*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void autocomplete_file(RLineCompletion *completion, const char *str) {
	r_return_if_fail (str);
	char *pipe = strchr (str, '>');

	if (pipe) {
		str = r_str_trim_ro (pipe + 1);
	}
	if (str && !*str) {
		autocomplete_process_path (completion, str, "./");
	} else {
		autocomplete_process_path (completion, str, str);
	}

}