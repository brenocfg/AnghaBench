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
 scalar_t__ EEXIST ; 
 int FAILURE ; 
 scalar_t__ IS_SLASH (char) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  S_IRWXU ; 
 scalar_t__ errno ; 
 scalar_t__ mkdir (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zend_file_cache_mkdir(char *filename, size_t start)
{
	char *s = filename + start;

	while (*s) {
		if (IS_SLASH(*s)) {
			char old = *s;
			*s = '\000';
#ifndef ZEND_WIN32
			if (mkdir(filename, S_IRWXU) < 0 && errno != EEXIST) {
#else
			if (php_win32_ioutil_mkdir(filename, 0700) < 0 && errno != EEXIST) {
#endif
				*s = old;
				return FAILURE;
			}
			*s = old;
		}
		s++;
	}
	return SUCCESS;
}