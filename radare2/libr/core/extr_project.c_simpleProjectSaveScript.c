#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* highlight; int fdout; TYPE_1__* context; } ;
struct TYPE_7__ {int /*<<< orphan*/  anal; int /*<<< orphan*/  config; } ;
struct TYPE_6__ {int is_interactive; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int O_BINARY ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int R_CORE_PRJ_EVAL ; 
 int R_CORE_PRJ_FCNS ; 
 int R_CORE_PRJ_FLAGS ; 
 int R_CORE_PRJ_META ; 
 int R_CORE_PRJ_XREFS ; 
 int /*<<< orphan*/  R_META_TYPE_ANY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_config_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int /*<<< orphan*/  r_cons_highlight (char*) ; 
 TYPE_5__* r_cons_singleton () ; 
 int /*<<< orphan*/  r_core_cmd (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_meta_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int r_sandbox_open (char const*,int,int) ; 
 char* r_str_word_get_first (char const*) ; 
 int /*<<< orphan*/  r_str_write (int,char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static bool simpleProjectSaveScript(RCore *core, const char *file, int opts) {
	char *filename, *hl, *ohl = NULL;
	int fd, fdold;

	if (!file || * file == '\0') {
		return false;
	}

	filename = r_str_word_get_first (file);
	fd = r_sandbox_open (file, O_BINARY | O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		free (filename);
		return false;
	}

	hl = r_cons_singleton ()->highlight;
	if (hl) {
		ohl = strdup (hl);
		r_cons_highlight (NULL);
	}

	fdold = r_cons_singleton ()->fdout;
	r_cons_singleton ()->fdout = fd;
	r_cons_singleton ()->context->is_interactive = false; // NOES must use api

	r_str_write (fd, "# r2 rdb project file\n");

	if (opts & R_CORE_PRJ_EVAL) {
		r_str_write (fd, "# eval\n");
		r_config_list (core->config, NULL, true);
		r_cons_flush ();
	}

	if (opts & R_CORE_PRJ_FCNS) {
		r_str_write (fd, "# functions\n");
		r_core_cmd (core, "afl*", 0);
		r_cons_flush ();
	}

	if (opts & R_CORE_PRJ_FLAGS) {
		r_str_write (fd, "# flags\n");
		r_core_cmd (core, "f.**", 0);
		r_cons_flush ();
	}
	if (opts & R_CORE_PRJ_META) {
		r_str_write (fd, "# meta\n");
		r_meta_list (core->anal, R_META_TYPE_ANY, 1);
		r_cons_flush ();
		r_core_cmd (core, "fV*", 0);
		r_cons_flush ();
	}
	if (opts & R_CORE_PRJ_XREFS) {
		r_str_write (fd, "# xrefs\n");
		r_core_cmd (core, "ax*", 0);
		r_cons_flush ();
	}


	r_cons_singleton ()->fdout = fdold;
	r_cons_singleton ()->context->is_interactive = true;

	if (ohl) {
		r_cons_highlight (ohl);
		free (ohl);
	}

	close (fd);
	free (filename);

	return true;
}