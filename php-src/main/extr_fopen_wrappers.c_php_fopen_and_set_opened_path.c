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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CWD_EXPAND ; 
 int /*<<< orphan*/ * VCWD_FOPEN (char const*,char const*) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* expand_filepath_with_mode (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ php_check_open_basedir (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * zend_string_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FILE *php_fopen_and_set_opened_path(const char *path, const char *mode, zend_string **opened_path)
{
	FILE *fp;

	if (php_check_open_basedir((char *)path)) {
		return NULL;
	}
	fp = VCWD_FOPEN(path, mode);
	if (fp && opened_path) {
		//TODO :avoid reallocation
		char *tmp = expand_filepath_with_mode(path, NULL, NULL, 0, CWD_EXPAND);
		if (tmp) {
			*opened_path = zend_string_init(tmp, strlen(tmp), 0);
			efree(tmp);
		}
	}
	return fp;
}