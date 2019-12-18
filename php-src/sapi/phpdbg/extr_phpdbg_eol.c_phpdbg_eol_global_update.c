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
 scalar_t__ strcmp (char*,char*) ; 

int phpdbg_eol_global_update(char *name)
{

	if (0 == strcmp(name, "CRLF") || 0 == strcmp(name, "crlf") || 0 == strcmp(name, "DOS") || 0 == strcmp(name, "dos")) {
		PHPDBG_G(eol) = PHPDBG_EOL_CRLF;
	} else if (0 == strcmp(name, "LF") || 0 == strcmp(name, "lf") || 0 == strcmp(name, "UNIX") || 0 == strcmp(name, "unix")) {
		PHPDBG_G(eol) = PHPDBG_EOL_LF;
	} else if (0 == strcmp(name, "CR") || 0 == strcmp(name, "cr") || 0 == strcmp(name, "MAC") || 0 == strcmp(name, "mac")) {
		PHPDBG_G(eol) = PHPDBG_EOL_CR;
	} else {
		return FAILURE;
	}

	return SUCCESS;
}