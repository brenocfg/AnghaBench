#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ std_strings; int /*<<< orphan*/  searchpath; int /*<<< orphan*/  encoding; TYPE_2__* ropt; } ;
struct TYPE_8__ {TYPE_1__ public; } ;
struct TYPE_7__ {scalar_t__ enable_row_security; scalar_t__ use_role; } ;
typedef  TYPE_2__ RestoreOptions ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ahprintf (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  fmtId (scalar_t__) ; 
 int /*<<< orphan*/  pg_encoding_to_char (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_doSetFixedOutputState(ArchiveHandle *AH)
{
	RestoreOptions *ropt = AH->public.ropt;

	/*
	 * Disable timeouts to allow for slow commands, idle parallel workers, etc
	 */
	ahprintf(AH, "SET statement_timeout = 0;\n");
	ahprintf(AH, "SET lock_timeout = 0;\n");
	ahprintf(AH, "SET idle_in_transaction_session_timeout = 0;\n");

	/* Select the correct character set encoding */
	ahprintf(AH, "SET client_encoding = '%s';\n",
			 pg_encoding_to_char(AH->public.encoding));

	/* Select the correct string literal syntax */
	ahprintf(AH, "SET standard_conforming_strings = %s;\n",
			 AH->public.std_strings ? "on" : "off");

	/* Select the role to be used during restore */
	if (ropt && ropt->use_role)
		ahprintf(AH, "SET ROLE %s;\n", fmtId(ropt->use_role));

	/* Select the dump-time search_path */
	if (AH->public.searchpath)
		ahprintf(AH, "%s", AH->public.searchpath);

	/* Make sure function checking is disabled */
	ahprintf(AH, "SET check_function_bodies = false;\n");

	/* Ensure that all valid XML data will be accepted */
	ahprintf(AH, "SET xmloption = content;\n");

	/* Avoid annoying notices etc */
	ahprintf(AH, "SET client_min_messages = warning;\n");
	if (!AH->public.std_strings)
		ahprintf(AH, "SET escape_string_warning = off;\n");

	/* Adjust row-security state */
	if (ropt && ropt->enable_row_security)
		ahprintf(AH, "SET row_security = on;\n");
	else
		ahprintf(AH, "SET row_security = off;\n");

	ahprintf(AH, "\n");
}