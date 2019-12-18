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
 int atoi (char const*) ; 

__attribute__((used)) static int sapi_extract_response_code(const char *header_line)
{
	int code = 200;
	const char *ptr;

	for (ptr = header_line; *ptr; ptr++) {
		if (*ptr == ' ' && *(ptr + 1) != ' ') {
			code = atoi(ptr + 1);
			break;
		}
	}

	return code;
}