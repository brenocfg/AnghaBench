#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prompt ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int /*<<< orphan*/  config; TYPE_1__* log; } ;
struct TYPE_7__ {int last; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ r_cons_fgets (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  r_core_log_add (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  r_core_log_list (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_line_set_prompt (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int textlog_chat(RCore *core) {
	char prompt[64];
	char buf[1024];
	int lastmsg = 0;
	const char *me = r_config_get (core->config, "cfg.user");
	char msg[2048];

	eprintf ("Type '/help' for commands:\n");
	snprintf (prompt, sizeof (prompt) - 1, "[%s]> ", me);
	r_line_set_prompt (prompt);
	for (;;) {
		r_core_log_list (core, lastmsg, 0, 0);
		lastmsg = core->log->last;
		if (r_cons_fgets (buf, sizeof (buf) - 1, 0, NULL) < 0) {
			return 1;
		}
		if (!*buf) {
			continue;
		}
		if (!strcmp (buf, "/help")) {
			eprintf ("/quit           quit the chat (same as ^D)\n");
			eprintf ("/name <nick>    set cfg.user name\n");
			eprintf ("/log            show full log\n");
			eprintf ("/clear          clear text log messages\n");
		} else if (!strncmp (buf, "/name ", 6)) {
			snprintf (msg, sizeof (msg) - 1, "* '%s' is now known as '%s'", me, buf + 6);
			r_core_log_add (core, msg);
			r_config_set (core->config, "cfg.user", buf + 6);
			me = r_config_get (core->config, "cfg.user");
			snprintf (prompt, sizeof (prompt) - 1, "[%s]> ", me);
			r_line_set_prompt (prompt);
			return 0;
		} else if (!strcmp (buf, "/log")) {
			r_core_log_list (core, 0, 0, 0);
			return 0;
		} else if (!strcmp (buf, "/clear")) {
			// r_core_log_del (core, 0);
			r_core_cmd0 (core, "T-");
			return 0;
		} else if (!strcmp (buf, "/quit")) {
			return 0;
		} else if (*buf == '/') {
			eprintf ("Unknown command: %s\n", buf);
		} else {
			snprintf (msg, sizeof (msg), "[%s] %s", me, buf);
			r_core_log_add (core, msg);
		}
	}
	return 1;
}