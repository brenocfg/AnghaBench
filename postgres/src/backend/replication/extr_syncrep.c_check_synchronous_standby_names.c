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
struct TYPE_3__ {scalar_t__ num_sync; int /*<<< orphan*/  config_size; } ;
typedef  int /*<<< orphan*/  SyncRepConfigData ;
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  GUC_check_errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GUC_check_errdetail (char*,...) ; 
 int /*<<< orphan*/  GUC_check_errmsg (char*,scalar_t__) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * syncrep_parse_error_msg ; 
 TYPE_1__* syncrep_parse_result ; 
 int /*<<< orphan*/  syncrep_scanner_finish () ; 
 int /*<<< orphan*/  syncrep_scanner_init (char*) ; 
 int syncrep_yyparse () ; 

bool
check_synchronous_standby_names(char **newval, void **extra, GucSource source)
{
	if (*newval != NULL && (*newval)[0] != '\0')
	{
		int			parse_rc;
		SyncRepConfigData *pconf;

		/* Reset communication variables to ensure a fresh start */
		syncrep_parse_result = NULL;
		syncrep_parse_error_msg = NULL;

		/* Parse the synchronous_standby_names string */
		syncrep_scanner_init(*newval);
		parse_rc = syncrep_yyparse();
		syncrep_scanner_finish();

		if (parse_rc != 0 || syncrep_parse_result == NULL)
		{
			GUC_check_errcode(ERRCODE_SYNTAX_ERROR);
			if (syncrep_parse_error_msg)
				GUC_check_errdetail("%s", syncrep_parse_error_msg);
			else
				GUC_check_errdetail("synchronous_standby_names parser failed");
			return false;
		}

		if (syncrep_parse_result->num_sync <= 0)
		{
			GUC_check_errmsg("number of synchronous standbys (%d) must be greater than zero",
							 syncrep_parse_result->num_sync);
			return false;
		}

		/* GUC extra value must be malloc'd, not palloc'd */
		pconf = (SyncRepConfigData *)
			malloc(syncrep_parse_result->config_size);
		if (pconf == NULL)
			return false;
		memcpy(pconf, syncrep_parse_result, syncrep_parse_result->config_size);

		*extra = (void *) pconf;

		/*
		 * We need not explicitly clean up syncrep_parse_result.  It, and any
		 * other cruft generated during parsing, will be freed when the
		 * current memory context is deleted.  (This code is generally run in
		 * a short-lived context used for config file processing, so that will
		 * not be very long.)
		 */
	}
	else
		*extra = NULL;

	return true;
}