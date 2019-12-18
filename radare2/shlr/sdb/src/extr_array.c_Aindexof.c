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
 int /*<<< orphan*/  SDB_RS ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *Aindexof(const char *str, int idx) {
	int len = 0;
	const char *n, *p = str;
	for (len = 0; ; len++) {
		if (len == idx) {
			return p;
		}
		if (!(n = strchr (p, SDB_RS))) {
			break;
		}
		p = n + 1;
	}
	return NULL;
}