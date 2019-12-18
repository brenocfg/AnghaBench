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
typedef  int /*<<< orphan*/  va_list ;
struct statement {int dummy; } ;
typedef  enum ECPG_statement_type { ____Placeholder_ECPG_statement_type } ECPG_statement_type ;

/* Variables and functions */
 int /*<<< orphan*/  ecpg_autostart_transaction (struct statement*) ; 
 int /*<<< orphan*/  ecpg_build_params (struct statement*) ; 
 int /*<<< orphan*/  ecpg_do_epilogue (struct statement*) ; 
 int /*<<< orphan*/  ecpg_do_prologue (int const,int const,int const,char const*,int const,int,char const*,int /*<<< orphan*/ ,struct statement**) ; 
 int /*<<< orphan*/  ecpg_execute (struct statement*) ; 
 int /*<<< orphan*/  ecpg_process_output (struct statement*,int) ; 

bool
ecpg_do(const int lineno, const int compat, const int force_indicator, const char *connection_name, const bool questionmarks, const int st, const char *query, va_list args)
{
	struct statement *stmt = NULL;

	if (!ecpg_do_prologue(lineno, compat, force_indicator, connection_name,
						  questionmarks, (enum ECPG_statement_type) st,
						  query, args, &stmt))
		goto fail;

	if (!ecpg_build_params(stmt))
		goto fail;

	if (!ecpg_autostart_transaction(stmt))
		goto fail;

	if (!ecpg_execute(stmt))
		goto fail;

	if (!ecpg_process_output(stmt, true))
		goto fail;

	ecpg_do_epilogue(stmt);
	return true;

fail:
	ecpg_do_epilogue(stmt);
	return false;
}