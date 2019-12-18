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
typedef  int /*<<< orphan*/  zend_stat_t ;
typedef  scalar_t__ zend_bool ;
struct phpdbg_init_state {char* init_file; char* code; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PHPDBG_MAX_CMD ; 
 int VCWD_STAT (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  phpdbg_error (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  phpdbg_line_init (char*,struct phpdbg_init_state*) ; 

void phpdbg_try_file_init(char *init_file, size_t init_file_len, zend_bool free_init) /* {{{ */
{
	zend_stat_t sb;

	if (init_file && VCWD_STAT(init_file, &sb) != -1) {
		FILE *fp = fopen(init_file, "r");
		if (fp) {
			char cmd[PHPDBG_MAX_CMD];
			struct phpdbg_init_state state = {0};

			state.init_file = init_file;

			while (fgets(cmd, PHPDBG_MAX_CMD, fp) != NULL) {
				phpdbg_line_init(cmd, &state);
			}

			if (state.code) {
				free(state.code);
			}

			fclose(fp);
		} else {
			phpdbg_error("initfailure", "type=\"openfile\" file=\"%s\"", "Failed to open %s for initialization", init_file);
		}

		if (free_init) {
			free(init_file);
		}
	}
}