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
 scalar_t__ IS_SLASH (char) ; 

__attribute__((used)) static char * php_zip_make_relative_path(char *path, size_t path_len) /* {{{ */
{
	char *path_begin = path;
	size_t i;

	if (path_len < 1 || path == NULL) {
		return NULL;
	}

	if (IS_SLASH(path[0])) {
		return path + 1;
	}

	i = path_len;

	while (1) {
		while (i > 0 && !IS_SLASH(path[i])) {
			i--;
		}

		if (!i) {
			return path;
		}

		if (i >= 2 && (path[i -1] == '.' || path[i -1] == ':')) {
			/* i is the position of . or :, add 1 for / */
			path_begin = path + i + 1;
			break;
		}
		i--;
	}

	return path_begin;
}