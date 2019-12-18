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
struct statement {char* command; int /*<<< orphan*/  lineno; } ;

/* Variables and functions */
 scalar_t__ ecpg_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecpg_free (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static bool
insert_tobeinserted(int position, int ph_len, struct statement *stmt, char *tobeinserted)
{
	char	   *newcopy;

	if (!(newcopy = (char *) ecpg_alloc(strlen(stmt->command)
										+ strlen(tobeinserted)
										+ 1, stmt->lineno)))
	{
		ecpg_free(tobeinserted);
		return false;
	}

	strcpy(newcopy, stmt->command);
	strcpy(newcopy + position - 1, tobeinserted);

	/*
	 * The strange thing in the second argument is the rest of the string from
	 * the old string
	 */
	strcat(newcopy,
		   stmt->command
		   + position
		   + ph_len - 1);

	ecpg_free(stmt->command);
	stmt->command = newcopy;

	ecpg_free(tobeinserted);
	return true;
}