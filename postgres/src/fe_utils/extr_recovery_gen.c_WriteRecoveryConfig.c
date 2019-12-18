#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int MAXPGPATH ; 
 scalar_t__ MINIMUM_VERSION_FOR_RECOVERY_GUC ; 
 scalar_t__ PQserverVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_log_error (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

void
WriteRecoveryConfig(PGconn *pgconn, char *target_dir, PQExpBuffer contents)
{
	char		filename[MAXPGPATH];
	FILE	   *cf;
	bool		use_recovery_conf;

	Assert(pgconn != NULL);

	use_recovery_conf =
		PQserverVersion(pgconn) < MINIMUM_VERSION_FOR_RECOVERY_GUC;

	snprintf(filename, MAXPGPATH, "%s/%s", target_dir,
			 use_recovery_conf ? "recovery.conf" : "postgresql.auto.conf");

	cf = fopen(filename, use_recovery_conf ? "a" : "w");
	if (cf == NULL)
	{
		pg_log_error("could not open file \"%s\": %m", filename);
		exit(1);
	}

	if (fwrite(contents->data, contents->len, 1, cf) != 1)
	{
		pg_log_error("could not write to file \"%s\": %m", filename);
		exit(1);
	}

	fclose(cf);

	if (!use_recovery_conf)
	{
		snprintf(filename, MAXPGPATH, "%s/%s", target_dir, "standby.signal");
		cf = fopen(filename, "w");
		if (cf == NULL)
		{
			pg_log_error("could not create file \"%s\": %m", filename);
			exit(1);
		}

		fclose(cf);
	}
}