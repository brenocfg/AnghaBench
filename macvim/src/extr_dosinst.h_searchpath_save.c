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
 char* alloc (scalar_t__) ; 
 char* searchpath (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *
searchpath_save(char *name)
{
    char	*p;
    char	*s;

    p = searchpath(name);
    if (p == NULL)
	return NULL;
    s = alloc(strlen(p) + 1);
    strcpy(s, p);
    return s;
}