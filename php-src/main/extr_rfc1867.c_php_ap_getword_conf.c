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
 char* estrdup (char*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ strlen (char*) ; 
 char* substring_conf (char*,int,char) ; 

__attribute__((used)) static char *php_ap_getword_conf(const zend_encoding *encoding, char *str)
{
	while (*str && isspace(*str)) {
		++str;
	}

	if (!*str) {
		return estrdup("");
	}

	if (*str == '"' || *str == '\'') {
		char quote = *str;

		str++;
		return substring_conf(str, (int)strlen(str), quote);
	} else {
		char *strend = str;

		while (*strend && !isspace(*strend)) {
			++strend;
		}
		return substring_conf(str, strend - str, 0);
	}
}