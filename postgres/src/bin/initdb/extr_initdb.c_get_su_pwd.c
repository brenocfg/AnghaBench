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
typedef  int /*<<< orphan*/  pwd2 ;
typedef  int /*<<< orphan*/  pwd1 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pg_log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_strdup (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  pwfilename ; 
 scalar_t__ pwprompt ; 
 int /*<<< orphan*/  simple_prompt (char*,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  superuser_password ; 

__attribute__((used)) static void
get_su_pwd(void)
{
	char		pwd1[100];
	char		pwd2[100];

	if (pwprompt)
	{
		/*
		 * Read password from terminal
		 */
		printf("\n");
		fflush(stdout);
		simple_prompt("Enter new superuser password: ", pwd1, sizeof(pwd1), false);
		simple_prompt("Enter it again: ", pwd2, sizeof(pwd2), false);
		if (strcmp(pwd1, pwd2) != 0)
		{
			fprintf(stderr, _("Passwords didn't match.\n"));
			exit(1);
		}
	}
	else
	{
		/*
		 * Read password from file
		 *
		 * Ideally this should insist that the file not be world-readable.
		 * However, this option is mainly intended for use on Windows where
		 * file permissions may not exist at all, so we'll skip the paranoia
		 * for now.
		 */
		FILE	   *pwf = fopen(pwfilename, "r");
		int			i;

		if (!pwf)
		{
			pg_log_error("could not open file \"%s\" for reading: %m",
						 pwfilename);
			exit(1);
		}
		if (!fgets(pwd1, sizeof(pwd1), pwf))
		{
			if (ferror(pwf))
				pg_log_error("could not read password from file \"%s\": %m",
							 pwfilename);
			else
				pg_log_error("password file \"%s\" is empty",
							 pwfilename);
			exit(1);
		}
		fclose(pwf);

		i = strlen(pwd1);
		while (i > 0 && (pwd1[i - 1] == '\r' || pwd1[i - 1] == '\n'))
			pwd1[--i] = '\0';
	}

	superuser_password = pg_strdup(pwd1);
}