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
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 scalar_t__ __plugin_open (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ gs ; 
 int /*<<< orphan*/ * r_io_desc_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int,int,scalar_t__) ; 
 int /*<<< orphan*/  r_io_plugin_winedbg ; 
 scalar_t__ r_socket_new (int /*<<< orphan*/ ) ; 
 int r_socket_spawn (scalar_t__,char*,int) ; 
 char* r_str_newf (char*,char const*) ; 
 char* runcmd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static RIODesc *__open(RIO *io, const char *pathname, int rw, int mode) {
	if (__plugin_open (io, pathname, 0)) {
		if (gs) {
			return NULL;
		}
		gs = r_socket_new (0);
		char *cmd = r_str_newf ("winedbg '%s'", pathname + 10);
		int res = r_socket_spawn (gs, cmd, 1000);
		free (cmd);
		if (!res) {
			return NULL;
		}
		char *reply = runcmd (NULL);
		if (reply) {
			int rw = 7;
			free (reply);
			eprintf ("Wine-dbg is ready to go!\n");
			return r_io_desc_new (io, &r_io_plugin_winedbg, pathname, rw, mode, gs);
		}
		eprintf ("Can't find the Wine-dbg prompt\n");
	}
	return NULL;
}