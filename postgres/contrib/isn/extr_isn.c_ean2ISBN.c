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
 int /*<<< orphan*/  hyphenate (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 unsigned int weight_checkdig (char*,int) ; 

__attribute__((used)) static inline void
ean2ISBN(char *isn)
{
	char	   *aux;
	unsigned	check;

	/*
	 * The number should come in this format: 978-0-000-00000-0 or may be an
	 * ISBN-13 number, 979-..., which does not have a short representation. Do
	 * the short output version if possible.
	 */
	if (strncmp("978-", isn, 4) == 0)
	{
		/* Strip the first part and calculate the new check digit */
		hyphenate(isn, isn + 4, NULL, NULL);
		check = weight_checkdig(isn, 10);
		aux = strchr(isn, '\0');
		while (!isdigit((unsigned char) *--aux));
		if (check == 10)
			*aux = 'X';
		else
			*aux = check + '0';
	}
}