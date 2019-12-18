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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int tolower (char) ; 

__attribute__((used)) static long to_kbytes(const char *string)
{
	int exp = 0;
	long result;
	char *end;

	result = strtoul(string, &end, 0);
	switch (tolower(*end)) {
		case 'k' :
		case '\0' : exp = 0; break;
		case 'm' : exp = 1; break;
		case 'g' : exp = 2; break;
		default: return 0;
	}

	if (*end)
		end++;

	if (*end) {
		fprintf(stderr, "garbage after end of number\n");
		return 0;
	}

	/* result: number + 1024^(exp) */
	if (exp == 0)
		return result;
	return result * (2 << ((10 * exp) - 1));
}