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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 char* strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

char *kdb_strdup(const char *str, gfp_t type)
{
	int n = strlen(str)+1;
	char *s = kmalloc(n, type);
	if (!s)
		return NULL;
	return strcpy(s, str);
}