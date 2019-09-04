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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int strlen (char const*) ; 
 char* strstr (char*,char const*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

int vreplace(char * string, const char * token, const char * fmt, va_list args)
{
	char data[64];
	char * pos;

	pos = strstr(string, token);
	if (!pos) {
		return 0;
	}

	vsnprintf(data, sizeof(data), fmt, args);

	memmove(pos + strlen(data), pos + strlen(token), strlen(pos + strlen(token)) + 1);
	memmove(pos, data, strlen(data));

	return 1;
}