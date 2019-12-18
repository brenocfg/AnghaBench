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
struct TYPE_3__ {int /*<<< orphan*/  rcmd; } ;
typedef  int /*<<< orphan*/  RLineCompletion ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 char** r_cmd_alias_keys (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  r_line_completion_push (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_return_if_fail (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static void autocomplete_minus(RCore *core, RLineCompletion *completion, const char *str) {
	r_return_if_fail (str);
	int count;
	int length = strlen (str);
	char **keys = r_cmd_alias_keys(core->rcmd, &count);
	if (!keys) {
		return;
	}
	int i;
	for (i = 0; i < count; i++) {
		if (!strncmp (keys[i], str, length)) {
			r_line_completion_push (completion, keys[i]);
		}
	}
}