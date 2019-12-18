#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  cwd ;
struct TYPE_2__ {int cwd_length; int /*<<< orphan*/  cwd; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  ZeroMemory (char**,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 char* getcwd (char*,int) ; 
 TYPE_1__ main_cwd_state ; 
 char* php_win32_ioutil_getcwd (char*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int strlen (char*) ; 
 char toupper (char) ; 

void virtual_cwd_main_cwd_init(uint8_t reinit) /* {{{ */
{
	char cwd[MAXPATHLEN];
	char *result;

	if (reinit) {
		free(main_cwd_state.cwd);
	}

#ifdef ZEND_WIN32
	ZeroMemory(&cwd, sizeof(cwd));
	result = php_win32_ioutil_getcwd(cwd, sizeof(cwd));
#else
	result = getcwd(cwd, sizeof(cwd));
#endif

	if (!result) {
		cwd[0] = '\0';
	}

	main_cwd_state.cwd_length = strlen(cwd);
#ifdef ZEND_WIN32
	if (main_cwd_state.cwd_length >= 2 && cwd[1] == ':') {
		cwd[0] = toupper(cwd[0]);
	}
#endif
	main_cwd_state.cwd = strdup(cwd);
}