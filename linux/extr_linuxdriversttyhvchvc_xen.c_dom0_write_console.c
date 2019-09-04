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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLEIO_write ; 
 int HYPERVISOR_console_io (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int dom0_write_console(uint32_t vtermno, const char *str, int len)
{
	int rc = HYPERVISOR_console_io(CONSOLEIO_write, len, (char *)str);
	if (rc < 0)
		return rc;

	return len;
}