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
struct TYPE_4__ {int read_pipe; int /*<<< orphan*/ * handle_err; int /*<<< orphan*/ * process; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ os_process_pipe_t ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HANDLE_FLAG_INHERIT ; 
 int /*<<< orphan*/  SetHandleInformation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* bmalloc (int) ; 
 int /*<<< orphan*/  create_pipe (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int create_process (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

os_process_pipe_t *os_process_pipe_create(const char *cmd_line,
					  const char *type)
{
	os_process_pipe_t *pp = NULL;
	bool read_pipe;
	HANDLE process;
	HANDLE output;
	HANDLE err_input, err_output;
	HANDLE input;
	bool success;

	if (!cmd_line || !type) {
		return NULL;
	}
	if (*type != 'r' && *type != 'w') {
		return NULL;
	}
	if (!create_pipe(&input, &output)) {
		return NULL;
	}

	if (!create_pipe(&err_input, &err_output)) {
		return NULL;
	}

	read_pipe = *type == 'r';

	success = !!SetHandleInformation(read_pipe ? input : output,
					 HANDLE_FLAG_INHERIT, false);
	if (!success) {
		goto error;
	}

	success = !!SetHandleInformation(err_input, HANDLE_FLAG_INHERIT, false);
	if (!success) {
		goto error;
	}

	success = create_process(cmd_line, read_pipe ? NULL : input,
				 read_pipe ? output : NULL, err_output,
				 &process);
	if (!success) {
		goto error;
	}

	pp = bmalloc(sizeof(*pp));

	pp->handle = read_pipe ? input : output;
	pp->read_pipe = read_pipe;
	pp->process = process;
	pp->handle_err = err_input;

	CloseHandle(read_pipe ? output : input);
	CloseHandle(err_output);
	return pp;

error:
	CloseHandle(output);
	CloseHandle(input);
	return NULL;
}