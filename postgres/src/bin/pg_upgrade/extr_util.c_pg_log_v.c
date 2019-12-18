#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  message ;
typedef  int eLogType ;
struct TYPE_2__ {scalar_t__ verbose; int /*<<< orphan*/ * internal; } ;

/* Variables and functions */
 char* MESSAGE_WIDTH ; 
#define  PG_FATAL 132 
#define  PG_REPORT 131 
#define  PG_STATUS 130 
#define  PG_VERBOSE 129 
#define  PG_WARNING 128 
 int QUERY_ALLOC ; 
 char* _ (char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 TYPE_1__ log_opts ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pg_log_v(eLogType type, const char *fmt, va_list ap)
{
	char		message[QUERY_ALLOC];

	vsnprintf(message, sizeof(message), _(fmt), ap);

	/* PG_VERBOSE and PG_STATUS are only output in verbose mode */
	/* fopen() on log_opts.internal might have failed, so check it */
	if (((type != PG_VERBOSE && type != PG_STATUS) || log_opts.verbose) &&
		log_opts.internal != NULL)
	{
		if (type == PG_STATUS)
			/* status messages need two leading spaces and a newline */
			fprintf(log_opts.internal, "  %s\n", message);
		else
			fprintf(log_opts.internal, "%s", message);
		fflush(log_opts.internal);
	}

	switch (type)
	{
		case PG_VERBOSE:
			if (log_opts.verbose)
				printf("%s", message);
			break;

		case PG_STATUS:
			/* for output to a display, do leading truncation and append \r */
			if (isatty(fileno(stdout)))
				/* -2 because we use a 2-space indent */
				printf("  %s%-*.*s\r",
				/* prefix with "..." if we do leading truncation */
					   strlen(message) <= MESSAGE_WIDTH - 2 ? "" : "...",
					   MESSAGE_WIDTH - 2, MESSAGE_WIDTH - 2,
				/* optional leading truncation */
					   strlen(message) <= MESSAGE_WIDTH - 2 ? message :
					   message + strlen(message) - MESSAGE_WIDTH + 3 + 2);
			else
				printf("  %s\n", message);
			break;

		case PG_REPORT:
		case PG_WARNING:
			printf("%s", message);
			break;

		case PG_FATAL:
			printf("\n%s", message);
			printf(_("Failure, exiting\n"));
			exit(1);
			break;

		default:
			break;
	}
	fflush(stdout);
}