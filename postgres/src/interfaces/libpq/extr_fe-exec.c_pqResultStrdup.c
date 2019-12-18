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
typedef  int /*<<< orphan*/  PGresult ;

/* Variables and functions */
 scalar_t__ pqResultAlloc (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

char *
pqResultStrdup(PGresult *res, const char *str)
{
	char	   *space = (char *) pqResultAlloc(res, strlen(str) + 1, false);

	if (space)
		strcpy(space, str);
	return space;
}