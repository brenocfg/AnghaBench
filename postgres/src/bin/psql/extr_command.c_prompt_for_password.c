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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* pg_strdup (char*) ; 
 char* psprintf (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  simple_prompt (char*,char*,int,int) ; 

__attribute__((used)) static char *
prompt_for_password(const char *username)
{
	char		buf[100];

	if (username == NULL || username[0] == '\0')
		simple_prompt("Password: ", buf, sizeof(buf), false);
	else
	{
		char	   *prompt_text;

		prompt_text = psprintf(_("Password for user %s: "), username);
		simple_prompt(prompt_text, buf, sizeof(buf), false);
		free(prompt_text);
	}
	return pg_strdup(buf);
}