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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  RSocket ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  R_SOCKET_PROTO_TCP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * r_socket_accept (int /*<<< orphan*/ *) ; 
 scalar_t__ r_socket_connect (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_socket_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_socket_listen (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_socket_new (int) ; 
 int /*<<< orphan*/ * r_socket_slurp (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  r_sys_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static ut8 *tcpme (const char *pathname, int *code, int *len) {
	pathname += 6;
	*code = 404;
#if __UNIX__
	r_sys_signal (SIGINT, SIG_IGN);
#endif
	if (*pathname == ':') {
		/* listen and wait for connection */
		RSocket *sl = r_socket_new (false);
		if (!r_socket_listen (sl, pathname + 1, NULL)) {
			eprintf ("Cannot listen\n");
			r_socket_free (sl);
			return NULL;
		}
		RSocket *sc = r_socket_accept (sl);
		ut8 *res = r_socket_slurp (sc, len);
		r_socket_free (sc);
		r_socket_free (sl);
		if (res) {
			*code = 200;
			return res;
		}
	} else {
		/* connect and slurp the end point */
		char *host = strdup (pathname);
		if (!host) {
			return NULL;
		}
		char *port = strchr (host, ':');
		if (port) {
			*port++ = 0;
			RSocket *s = r_socket_new (false);
			if (r_socket_connect (s, host, port, R_SOCKET_PROTO_TCP, 0)) {
				ut8 *res = r_socket_slurp (s, len);
				if (*len < 1) {
					R_FREE (res);
				} else {
					*code = 200;
				}
				r_socket_free (s);
				free (host);
				return res;
			}
			r_socket_free (s);
		} else {
			eprintf ("Missing port.\n");
		}
		free (host);
	}
	return NULL;
}