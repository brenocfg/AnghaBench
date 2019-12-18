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
typedef  int /*<<< orphan*/  fullname ;

/* Variables and functions */
 int MAXPGPATH ; 
 int O_RDONLY ; 
 int PG_BINARY ; 
 int TZ_STRLEN_MAX ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 char const* pg_TZDIR () ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

int
pg_open_tzfile(const char *name, char *canonname)
{
	char		fullname[MAXPGPATH];

	if (canonname)
		strlcpy(canonname, name, TZ_STRLEN_MAX + 1);

	strlcpy(fullname, pg_TZDIR(), sizeof(fullname));
	if (strlen(fullname) + 1 + strlen(name) >= MAXPGPATH)
		return -1;				/* not gonna fit */
	strcat(fullname, "/");
	strcat(fullname, name);

	return open(fullname, O_RDONLY | PG_BINARY, 0);
}