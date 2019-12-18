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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  pg_log_error (char*,char const*) ; 
 scalar_t__ pwfilename ; 
 scalar_t__ pwprompt ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
check_need_password(const char *authmethodlocal, const char *authmethodhost)
{
	if ((strcmp(authmethodlocal, "md5") == 0 ||
		 strcmp(authmethodlocal, "password") == 0 ||
		 strcmp(authmethodlocal, "scram-sha-256") == 0) &&
		(strcmp(authmethodhost, "md5") == 0 ||
		 strcmp(authmethodhost, "password") == 0 ||
		 strcmp(authmethodhost, "scram-sha-256") == 0) &&
		!(pwprompt || pwfilename))
	{
		pg_log_error("must specify a password for the superuser to enable %s authentication",
					 (strcmp(authmethodlocal, "md5") == 0 ||
					  strcmp(authmethodlocal, "password") == 0 ||
					  strcmp(authmethodlocal, "scram-sha-256") == 0)
					 ? authmethodlocal
					 : authmethodhost);
		exit(1);
	}
}