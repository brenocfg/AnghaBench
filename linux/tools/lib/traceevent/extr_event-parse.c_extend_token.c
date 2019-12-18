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
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int extend_token(char **tok, char *buf, int size)
{
	char *newtok = realloc(*tok, size);

	if (!newtok) {
		free(*tok);
		*tok = NULL;
		return -1;
	}

	if (!*tok)
		strcpy(newtok, buf);
	else
		strcat(newtok, buf);
	*tok = newtok;

	return 0;
}