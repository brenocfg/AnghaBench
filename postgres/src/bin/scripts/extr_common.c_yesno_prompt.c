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
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  prompt ;

/* Variables and functions */
 char* PG_NOLETTER ; 
 char* PG_YESLETTER ; 
 char* _ (char const*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  simple_prompt (char*,char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

bool
yesno_prompt(const char *question)
{
	char		prompt[256];

	/*------
	   translator: This is a question followed by the translated options for
	   "yes" and "no". */
	snprintf(prompt, sizeof(prompt), _("%s (%s/%s) "),
			 _(question), _(PG_YESLETTER), _(PG_NOLETTER));

	for (;;)
	{
		char		resp[10];

		simple_prompt(prompt, resp, sizeof(resp), true);

		if (strcmp(resp, _(PG_YESLETTER)) == 0)
			return true;
		if (strcmp(resp, _(PG_NOLETTER)) == 0)
			return false;

		printf(_("Please answer \"%s\" or \"%s\".\n"),
			   _(PG_YESLETTER), _(PG_NOLETTER));
	}
}