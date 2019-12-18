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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static unsigned int parse_cid(const char *str)
{
	char *endptr = NULL;
	unsigned long int n;

	errno = 0;
	n = strtoul(str, &endptr, 10);
	if (errno || *endptr != '\0') {
		fprintf(stderr, "malformed CID \"%s\"\n", str);
		exit(EXIT_FAILURE);
	}
	return n;
}