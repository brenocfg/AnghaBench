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
 int KDB_NOENVVALUE ; 
 int KDB_NOTENV ; 
 char* kdbgetenv (char const*) ; 
 unsigned long simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int kdbgetulenv(const char *match, unsigned long *value)
{
	char *ep;

	ep = kdbgetenv(match);
	if (!ep)
		return KDB_NOTENV;
	if (strlen(ep) == 0)
		return KDB_NOENVVALUE;

	*value = simple_strtoul(ep, NULL, 0);

	return 0;
}