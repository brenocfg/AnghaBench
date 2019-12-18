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
 scalar_t__ isalnum (unsigned char) ; 

__attribute__((used)) static char *
clean_encoding_name(const char *key, char *newkey)
{
	const char *p;
	char	   *np;

	for (p = key, np = newkey; *p != '\0'; p++)
	{
		if (isalnum((unsigned char) *p))
		{
			if (*p >= 'A' && *p <= 'Z')
				*np++ = *p + 'a' - 'A';
			else
				*np++ = *p;
		}
	}
	*np = '\0';
	return newkey;
}