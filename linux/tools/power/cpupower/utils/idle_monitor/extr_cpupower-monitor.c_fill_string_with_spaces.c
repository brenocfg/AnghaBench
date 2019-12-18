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
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

int fill_string_with_spaces(char *s, int n)
{
	char *temp;
	int len = strlen(s);

	if (len >= n)
		return -1;

	temp = malloc(sizeof(char) * (n+1));
	for (; len < n; len++)
		s[len] = ' ';
	s[len] = '\0';
	snprintf(temp, n+1, " %s", s);
	strcpy(s, temp);
	free(temp);
	return 0;
}