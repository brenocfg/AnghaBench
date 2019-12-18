#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  prompt2 ;
typedef  int /*<<< orphan*/  prompt ;
struct TYPE_4__ {char* member_0; char* member_1; char* member_2; } ;
typedef  TYPE_1__ TextLog ;
typedef  int /*<<< orphan*/  RSocket ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int /*<<< orphan*/  r_core_rtr_cmd (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  r_line_hist_add (char const*) ; 
 char* r_line_readline () ; 
 int /*<<< orphan*/  r_line_set_prompt (char*) ; 
 int /*<<< orphan*/  r_socket_free (int /*<<< orphan*/ *) ; 
 char* r_socket_http_get (char*,int /*<<< orphan*/ *,int*) ; 
 char* r_str_newf (char*,...) ; 
 char* r_str_uri_encode (char const*) ; 
 int /*<<< orphan*/  rtr_textlog_chat (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  rtr_visual (int /*<<< orphan*/ *,TYPE_1__,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static void __rtr_shell(RCore *core, int nth) {
	char *proto = "http";
	char *host = "";
	char *port= "";
	char *file= "";
	char prompt[64], prompt2[64], *str, *ptr;
	int len;
	const char* res;
	RSocket *s = NULL;

	TextLog T = { host, port, file };
	snprintf (prompt, sizeof (prompt), "[%s://%s:%s/%s]> ",
			proto, host, port, file);
	snprintf (prompt2, sizeof (prompt2), "[%s:%s]$ ", host, port);
	for (;;) {
		r_line_set_prompt (prompt);
		res = r_line_readline ();
		if (!res || !*res) {
			break;
		}
		if (*res == 'q') {
			break;
		}
		if (!strcmp (res, "!sh")) {
			for (;;) {
				r_line_set_prompt (prompt2);
				res = r_line_readline ();
				if (!res || !*res || !strcmp (res, "exit")) {
					break;
				}
				ptr = r_str_uri_encode (res);
				char *uri = r_str_newf ("http://%s:%s/%s!%s", host, port, file, res);
				str = r_socket_http_get (uri, NULL, &len);
				if (str) {
					str[len] = 0;
					res = strstr (str, "\n\n");
					if (res) {
						res = strstr (res + 1, "\n\n");
					}
					res = res? res + 2: str;
					const char *tail = (res[strlen (res) - 1] == '\n')? "": "\n";
					printf ("%s%s", res, tail);
					r_line_hist_add (str);
					free (str);
				}
				free (ptr);
				free (uri);
			}
		} else if (res[0]=='v' || res[0] == 'V') {
			if (res[1]==' ') {
				rtr_visual (core, T, res + 1);
			} else {
				rtr_visual (core, T, NULL);
			}
		} else if (!strcmp (res, "TT")) {
			rtr_textlog_chat (core, T);
		} else {
			char *cmdline = r_str_newf ("%d %s", nth, res);
			r_core_rtr_cmd (core, cmdline);
			r_cons_flush ();
			r_line_hist_add (res);
		}
	}
	r_socket_free (s);
}