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
struct TYPE_5__ {int* input; int* output; } ;
typedef  TYPE_1__ R2Pipe ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_sys_getenv (char*) ; 

__attribute__((used)) static R2Pipe* r2pipe_open_spawn(R2Pipe* r2pipe) {
#if __UNIX__
	char *out = r_sys_getenv ("R2PIPE_IN");
	char *in = r_sys_getenv ("R2PIPE_OUT");
	int done = false;
	if (in && out) {
		int i_in = atoi (in);
		int i_out = atoi (out);
		if (i_in >= 0 && i_out >= 0) {
			r2pipe->input[0] = r2pipe->input[1] = i_in;
			r2pipe->output[0] = r2pipe->output[1] = i_out;
			done = true;
		}
	}
	if (!done) {
		eprintf ("Cannot find R2PIPE_IN or R2PIPE_OUT environment\n");
		R_FREE (r2pipe);
	}
	free (in);
	free (out);
	return r2pipe;
#else
	eprintf ("r2pipe_open(NULL) not supported on windows\n");
	return NULL;
#endif
}