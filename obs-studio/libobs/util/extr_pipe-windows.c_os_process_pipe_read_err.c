#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  handle_err; } ;
typedef  TYPE_1__ os_process_pipe_t ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t GetLastError () ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t*,int /*<<< orphan*/ *) ; 

size_t os_process_pipe_read_err(os_process_pipe_t *pp, uint8_t *data,
				size_t len)
{
	DWORD bytes_read;
	bool success;

	if (!pp || !pp->handle_err) {
		return 0;
	}

	success =
		!!ReadFile(pp->handle_err, data, (DWORD)len, &bytes_read, NULL);
	if (success && bytes_read) {
		return bytes_read;
	} else
		bytes_read = GetLastError();

	return 0;
}