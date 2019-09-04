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
typedef  int /*<<< orphan*/  PHPDBG_G ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  PHPDBG_EOL_CR ; 
 int /*<<< orphan*/  PHPDBG_EOL_CRLF ; 
 int /*<<< orphan*/  PHPDBG_EOL_LF ; 
 int SUCCESS ; 
 scalar_t__ memcmp (char*,char*,int) ; 

int phpdbg_eol_global_update(char *name)
{

	if (0 == memcmp(name, "CRLF", 4) || 0 == memcmp(name, "crlf", 4) || 0 == memcmp(name, "DOS", 3) || 0 == memcmp(name, "dos", 3)) {
		PHPDBG_G(eol) = PHPDBG_EOL_CRLF;
	} else if (0 == memcmp(name, "LF", 2) || 0 == memcmp(name, "lf", 2) || 0 == memcmp(name, "UNIX", 4) || 0 == memcmp(name, "unix", 4)) {
		PHPDBG_G(eol) = PHPDBG_EOL_LF;
	} else if (0 == memcmp(name, "CR", 2) || 0 == memcmp(name, "cr", 2) || 0 == memcmp(name, "MAC", 3) || 0 == memcmp(name, "mac", 3)) {
		PHPDBG_G(eol) = PHPDBG_EOL_CR;
	} else {
		return FAILURE;
	}

	return SUCCESS;
}