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
 int atoi (char*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r2cmd (int,int,char*) ; 
 char* r_sys_getenv (char*) ; 

__attribute__((used)) static int r_main_r2pipe(int argc, char **argv) {
        int i, rc = 0;
        char *_in = r_sys_getenv ("R2PIPE_IN");
        char *_out = r_sys_getenv ("R2PIPE_OUT");
        if (_in && _out) {
		int in = atoi (_in);
		int out = atoi (_out);
		for (i = 1; i < argc; i++) {
			r2cmd (in, out, argv[i]);
		}
        } else {
		eprintf ("Error: R2PIPE_(IN|OUT) environment not set\n");
		eprintf ("Usage: r2 -c '!*r2p x' # run commands via r2pipe\n");
                rc = 1;
	}
	free (_in);
	free (_out);
        return rc;
}