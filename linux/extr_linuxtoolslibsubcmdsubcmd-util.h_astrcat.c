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
 int asprintf (char**,char*,char*,char const*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static inline void astrcat(char **out, const char *add)
{
	char *tmp = *out;

	if (asprintf(out, "%s%s", tmp ?: "", add) == -1)
		die("asprintf failed");

	free(tmp);
}