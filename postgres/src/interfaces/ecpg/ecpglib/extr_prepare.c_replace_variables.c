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
 int CHAR_BIT ; 
 scalar_t__ ecpg_alloc (int,int) ; 
 int /*<<< orphan*/  ecpg_free (char*) ; 
 scalar_t__ isvarchar (char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static bool
replace_variables(char **text, int lineno)
{
	bool		string = false;
	int			counter = 1,
				ptr = 0;

	for (; (*text)[ptr] != '\0'; ptr++)
	{
		if ((*text)[ptr] == '\'')
			string = string ? false : true;

		if (string || (((*text)[ptr] != ':') && ((*text)[ptr] != '?')))
			continue;

		if (((*text)[ptr] == ':') && ((*text)[ptr + 1] == ':'))
			ptr += 2;			/* skip  '::' */
		else
		{
			/* a rough guess of the size we need: */
			int			buffersize = sizeof(int) * CHAR_BIT * 10 / 3;
			int			len;
			char	   *buffer,
					   *newcopy;

			if (!(buffer = (char *) ecpg_alloc(buffersize, lineno)))
				return false;

			snprintf(buffer, buffersize, "$%d", counter++);

			for (len = 1; (*text)[ptr + len] && isvarchar((*text)[ptr + len]); len++)
				 /* skip */ ;
			if (!(newcopy = (char *) ecpg_alloc(strlen(*text) -len + strlen(buffer) + 1, lineno)))
			{
				ecpg_free(buffer);
				return false;
			}

			memcpy(newcopy, *text, ptr);
			strcpy(newcopy + ptr, buffer);
			strcat(newcopy, (*text) +ptr + len);

			ecpg_free(*text);
			ecpg_free(buffer);

			*text = newcopy;

			if ((*text)[ptr] == '\0')	/* we reached the end */
				ptr--;			/* since we will (*text)[ptr]++ in the top
								 * level for loop */
		}
	}
	return true;
}