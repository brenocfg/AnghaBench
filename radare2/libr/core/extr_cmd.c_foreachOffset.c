#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_5__ {int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int /*<<< orphan*/  r_core_cmd (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_num_math (int /*<<< orphan*/ ,char const*) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void foreachOffset(RCore *core, const char *_cmd, const char *each) {
	char *cmd = strdup (_cmd);
	char *nextLine = NULL;
	ut64 addr;
	/* foreach list of items */
	while (each) {
		// skip spaces
		while (*each == ' ') {
			each++;
		}
		// stahp if empty string
		if (!*each) {
			break;
		}
		// find newline
		char *nl = strchr (each, '\n');
		if (nl) {
			*nl = 0;
			nextLine = nl + 1;
		} else {
			nextLine = NULL;
		}
		// chop comment in line
		nl = strchr (each, '#');
		if (nl) {
			*nl = 0;
		}
		// space separated numbers
		while (each && *each) {
			// find spaces
			while (*each == ' ') {
				each++;
			}
			char *str = strchr (each, ' ');
			if (str) {
				*str = '\0';
				addr = r_num_math (core->num, each);
				*str = ' ';
				each = str + 1;
			} else {
				if (!*each) {
					break;
				}
				addr = r_num_math (core->num, each);
				each = NULL;
			}
			r_core_seek (core, addr, 1);
			r_core_cmd (core, cmd, 0);
			r_cons_flush ();
		}
		each = nextLine;
	}
	free (cmd);
}