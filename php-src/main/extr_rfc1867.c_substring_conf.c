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
 char* emalloc (int) ; 

__attribute__((used)) static char *substring_conf(char *start, int len, char quote)
{
	char *result = emalloc(len + 1);
	char *resp = result;
	int i;

	for (i = 0; i < len && start[i] != quote; ++i) {
		if (start[i] == '\\' && (start[i + 1] == '\\' || (quote && start[i + 1] == quote))) {
			*resp++ = start[++i];
		} else {
			*resp++ = start[i];
		}
	}

	*resp = '\0';
	return result;
}