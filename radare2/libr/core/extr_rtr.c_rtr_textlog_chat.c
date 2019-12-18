#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prompt ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  TextLog ;
struct TYPE_6__ {int /*<<< orphan*/  prompt; } ;
struct TYPE_5__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ r_cons_fgets (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_println (char*) ; 
 int /*<<< orphan*/  r_core_log_add (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  r_line_set_prompt (char*) ; 
 TYPE_3__* r_line_singleton () ; 
 char* r_str_newf (char*,char const*,char*) ; 
 char* rtrcmd (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void rtr_textlog_chat (RCore *core, TextLog T) {
	char prompt[64];
	char buf[1024];
	int lastmsg = 0;
	const char *me = r_config_get (core->config, "cfg.user");
	char *ret, msg[1024];

	eprintf ("Type '/help' for commands and ^D to quit:\n");
	char *oldprompt = strdup (r_line_singleton ()->prompt);
	snprintf (prompt, sizeof (prompt) - 1, "[%s]> ", me);
	r_line_set_prompt (prompt);
	ret = rtrcmd (T, msg);
	for (;;) {
		if (lastmsg >= 0) {
			snprintf (msg, sizeof (msg) - 1, "T %d", lastmsg);
		} else {
			strcpy (msg, "T");
		}
		ret = rtrcmd (T, msg);
		r_cons_println (ret);
		free (ret);
		ret = rtrcmd (T, "Tl");
		lastmsg = atoi (ret)-1;
		free (ret);
		if (r_cons_fgets (buf, sizeof (buf) - 1, 0, NULL) < 0) {
			goto beach;
		}
		if (!*buf) {
			continue;
		}
		if (!strcmp (buf, "/help")) {
			eprintf ("/quit           quit the chat (same as ^D)\n");
			eprintf ("/nick <nick>    set cfg.user nick name\n");
			eprintf ("/log            show full log\n");
			eprintf ("/clear          clear text log messages\n");
		} else if (!strncmp (buf, "/nick ", 6)) {
			snprintf (msg, sizeof (msg) - 1, "* '%s' is now known as '%s'", me, buf+6);
			r_cons_println (msg);
			r_core_log_add (core, msg);
			r_config_set (core->config, "cfg.user", buf+6);
			me = r_config_get (core->config, "cfg.user");
			snprintf (prompt, sizeof (prompt) - 1, "[%s]> ", me);
			r_line_set_prompt (prompt);
		} else if (!strcmp (buf, "/log")) {
			char *ret = rtrcmd (T, "T");
			if (ret) {
				r_cons_println (ret);
				free (ret);
			}
		} else if (!strcmp (buf, "/clear")) {
			//r_core_log_del (core, 0);
			free (rtrcmd (T, "T-"));
		} else if (!strcmp (buf, "/quit")) {
			goto beach;
		} else if (*buf=='/') {
			eprintf ("Unknown command: %s\n", buf);
		} else {
			char *cmd = r_str_newf ("T [%s] %s", me, buf);
			free (rtrcmd (T, cmd));
			free (cmd);
		}
	}
beach:
	r_line_set_prompt (oldprompt);
	free (oldprompt);
}