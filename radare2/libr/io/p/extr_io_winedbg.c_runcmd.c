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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gs ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_socket_block_time (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_socket_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  r_socket_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 char* r_str_append (char*,char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static char *runcmd (const char *cmd) {
	char buf[4096] = {0};
	if (cmd) {
		r_socket_printf (gs, "%s\n", cmd);
	}
	int timeout = 1000000;
	char *str = NULL;
	r_socket_block_time (gs, 1, timeout, 0);
	while (true) {
		memset (buf, 0, sizeof (buf));
		r_socket_read (gs, (ut8*)buf, sizeof (buf) - 1); // NULL-terminate the string always
		char *promptFound = strstr (buf, "Wine-dbg>");
		if (promptFound) {
			*promptFound = 0;
			return r_str_append (str, buf);
		}
		str = r_str_append (str, buf);
	}
	free (str);
	return NULL;
}