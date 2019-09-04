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
typedef  int /*<<< orphan*/  zend_encoding ;

/* Variables and functions */
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *php_ap_basename(const zend_encoding *encoding, char *path)
{
	char *s = strrchr(path, '\\');
	char *s2 = strrchr(path, '/');

	if (s && s2) {
		if (s > s2) {
			++s;
		} else {
			s = ++s2;
		}
		return s;
	} else if (s) {
		return ++s;
	} else if (s2) {
		return ++s2;
	}
	return path;
}