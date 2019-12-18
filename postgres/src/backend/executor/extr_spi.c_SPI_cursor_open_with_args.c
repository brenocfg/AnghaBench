#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cursor_options; int nargs; int /*<<< orphan*/ * parserSetupArg; int /*<<< orphan*/ * parserSetup; int /*<<< orphan*/ * argtypes; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ _SPI_plan ;
typedef  int /*<<< orphan*/  Portal ;
typedef  int /*<<< orphan*/  ParamListInfo ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SPI_cursor_open_internal (char const*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SPI_result ; 
 int /*<<< orphan*/  _SPI_PLAN_MAGIC ; 
 scalar_t__ _SPI_begin_call (int) ; 
 int /*<<< orphan*/  _SPI_convert_params (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  _SPI_end_call (int) ; 
 int /*<<< orphan*/  _SPI_prepare_plan (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

Portal
SPI_cursor_open_with_args(const char *name,
						  const char *src,
						  int nargs, Oid *argtypes,
						  Datum *Values, const char *Nulls,
						  bool read_only, int cursorOptions)
{
	Portal		result;
	_SPI_plan	plan;
	ParamListInfo paramLI;

	if (src == NULL || nargs < 0)
		elog(ERROR, "SPI_cursor_open_with_args called with invalid arguments");

	if (nargs > 0 && (argtypes == NULL || Values == NULL))
		elog(ERROR, "SPI_cursor_open_with_args called with missing parameters");

	SPI_result = _SPI_begin_call(true);
	if (SPI_result < 0)
		elog(ERROR, "SPI_cursor_open_with_args called while not connected");

	memset(&plan, 0, sizeof(_SPI_plan));
	plan.magic = _SPI_PLAN_MAGIC;
	plan.cursor_options = cursorOptions;
	plan.nargs = nargs;
	plan.argtypes = argtypes;
	plan.parserSetup = NULL;
	plan.parserSetupArg = NULL;

	/* build transient ParamListInfo in executor context */
	paramLI = _SPI_convert_params(nargs, argtypes,
								  Values, Nulls);

	_SPI_prepare_plan(src, &plan);

	/* We needn't copy the plan; SPI_cursor_open_internal will do so */

	result = SPI_cursor_open_internal(name, &plan, paramLI, read_only);

	/* And clean up */
	_SPI_end_call(true);

	return result;
}