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
typedef  int /*<<< orphan*/  REgg ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_println (char*) ; 
 char* r_egg_option_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_egg_option_set (int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static void cmd_egg_option(REgg *egg, const char *key, const char *input) {
	if (!*input) {
		return;
	}
	if (input[1] != ' ') {
		char *a = r_egg_option_get (egg, key);
		if (a) {
			r_cons_println (a);
			free (a);
		}
	} else {
		r_egg_option_set (egg, key, input + 2);
	}
}