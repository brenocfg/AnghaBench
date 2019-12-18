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
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static char *
read_attr_value(char **input, char attr, PQExpBuffer errorMessage)
{
	char	   *begin = *input;
	char	   *end;

	if (*begin != attr)
	{
		printfPQExpBuffer(errorMessage,
						  libpq_gettext("malformed SCRAM message (attribute \"%c\" expected)\n"),
						  attr);
		return NULL;
	}
	begin++;

	if (*begin != '=')
	{
		printfPQExpBuffer(errorMessage,
						  libpq_gettext("malformed SCRAM message (expected character \"=\" for attribute \"%c\")\n"),
						  attr);
		return NULL;
	}
	begin++;

	end = begin;
	while (*end && *end != ',')
		end++;

	if (*end)
	{
		*end = '\0';
		*input = end + 1;
	}
	else
		*input = end;

	return begin;
}