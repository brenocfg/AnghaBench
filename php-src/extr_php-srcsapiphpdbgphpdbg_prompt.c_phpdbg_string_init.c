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
struct phpdbg_init_state {scalar_t__ code; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  phpdbg_line_init (char*,struct phpdbg_init_state*) ; 
 char* strtok (char*,char*) ; 

void phpdbg_string_init(char *buffer) {
	struct phpdbg_init_state state = {0};
	char *str = strtok(buffer, "\n");

	while (str) {
		phpdbg_line_init(str, &state);

		str = strtok(NULL, "\n");
	}

	if (state.code) {
		free(state.code);
	}
}