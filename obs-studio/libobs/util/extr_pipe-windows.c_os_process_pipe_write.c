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
struct TYPE_3__ {int /*<<< orphan*/  handle; scalar_t__ read_pipe; } ;
typedef  TYPE_1__ os_process_pipe_t ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,size_t*,int /*<<< orphan*/ *) ; 

size_t os_process_pipe_write(os_process_pipe_t *pp, const uint8_t *data,
			     size_t len)
{
	DWORD bytes_written;
	bool success;

	if (!pp) {
		return 0;
	}
	if (pp->read_pipe) {
		return 0;
	}

	success =
		!!WriteFile(pp->handle, data, (DWORD)len, &bytes_written, NULL);
	if (success && bytes_written) {
		return bytes_written;
	}

	return 0;
}