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
typedef  int /*<<< orphan*/  PsqlScanState ;
typedef  int /*<<< orphan*/  PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  OT_NORMAL ; 
 int /*<<< orphan*/  appendPQExpBufferChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  createPQExpBuffer () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* psql_scan_slash_option (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static PQExpBuffer
gather_boolean_expression(PsqlScanState scan_state)
{
	PQExpBuffer exp_buf = createPQExpBuffer();
	int			num_options = 0;
	char	   *value;

	/* collect all arguments for the conditional command into exp_buf */
	while ((value = psql_scan_slash_option(scan_state,
										   OT_NORMAL, NULL, false)) != NULL)
	{
		/* add spaces between tokens */
		if (num_options > 0)
			appendPQExpBufferChar(exp_buf, ' ');
		appendPQExpBufferStr(exp_buf, value);
		num_options++;
		free(value);
	}

	return exp_buf;
}