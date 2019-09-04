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
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 char* cli_completion_generator_ht (char const*,size_t,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ini_directives ; 
 char* malloc (scalar_t__) ; 
 char rl_completion_append_character ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static char *cli_completion_generator_ini(const char *text, size_t textlen, int *state) /* {{{ */
{
	char *retval, *tmp;

	tmp = retval = cli_completion_generator_ht(text + 1, textlen - 1, state, EG(ini_directives), NULL);
	if (retval) {
		retval = malloc(strlen(tmp) + 2);
		retval[0] = '#';
		strcpy(&retval[1], tmp);
		rl_completion_append_character = '=';
	}
	return retval;
}