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

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_str_new (char const*) ; 

__attribute__((used)) static char *parsePanelsConfig(const char *cfg, int len) {
	if (!cfg || !*cfg || len < 2 || *cfg != '[') {
		eprintf ("Not valid config!\n");
		return NULL;
	}
	char *tmp = r_str_new (cfg + 1);
	int i = 0;
	for (; i < len; i++) {
		if (tmp[i] == '}' && i + 1 < len) {
			if (tmp[i + 1] == ',') {
				tmp[i + 1] = '\n';
				continue;
			}
			if (tmp[i + 1] == ']') {
				tmp[i + 1] = '\n';
				break;
			}
			eprintf ("Not valid config!\n");
			free (tmp);
			return NULL;
		}
	}
	return tmp;
}