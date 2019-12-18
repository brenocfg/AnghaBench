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
typedef  int /*<<< orphan*/  needle ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static bool cmp_str_seq(const char *log, const char *exp)
{
	char needle[80];
	const char *p, *q;
	int len;

	do {
		p = strchr(exp, '\t');
		if (!p)
			p = exp + strlen(exp);

		len = p - exp;
		if (len >= sizeof(needle) || !len) {
			printf("FAIL\nTestcase bug\n");
			return false;
		}
		strncpy(needle, exp, len);
		needle[len] = 0;
		q = strstr(log, needle);
		if (!q) {
			printf("FAIL\nUnexpected verifier log in successful load!\n"
			       "EXP: %s\nRES:\n", needle);
			return false;
		}
		log = q + len;
		exp = p + 1;
	} while (*p);
	return true;
}