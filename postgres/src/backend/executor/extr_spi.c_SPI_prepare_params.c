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
struct TYPE_5__ {int cursor_options; void* parserSetupArg; int /*<<< orphan*/  parserSetup; int /*<<< orphan*/ * argtypes; scalar_t__ nargs; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ _SPI_plan ;
typedef  int /*<<< orphan*/ * SPIPlanPtr ;
typedef  int /*<<< orphan*/  ParserSetupHook ;

/* Variables and functions */
 scalar_t__ SPI_ERROR_ARGUMENT ; 
 scalar_t__ SPI_result ; 
 int /*<<< orphan*/  _SPI_PLAN_MAGIC ; 
 scalar_t__ _SPI_begin_call (int) ; 
 int /*<<< orphan*/  _SPI_end_call (int) ; 
 int /*<<< orphan*/ * _SPI_make_plan_non_temp (TYPE_1__*) ; 
 int /*<<< orphan*/  _SPI_prepare_plan (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

SPIPlanPtr
SPI_prepare_params(const char *src,
				   ParserSetupHook parserSetup,
				   void *parserSetupArg,
				   int cursorOptions)
{
	_SPI_plan	plan;
	SPIPlanPtr	result;

	if (src == NULL)
	{
		SPI_result = SPI_ERROR_ARGUMENT;
		return NULL;
	}

	SPI_result = _SPI_begin_call(true);
	if (SPI_result < 0)
		return NULL;

	memset(&plan, 0, sizeof(_SPI_plan));
	plan.magic = _SPI_PLAN_MAGIC;
	plan.cursor_options = cursorOptions;
	plan.nargs = 0;
	plan.argtypes = NULL;
	plan.parserSetup = parserSetup;
	plan.parserSetupArg = parserSetupArg;

	_SPI_prepare_plan(src, &plan);

	/* copy plan to procedure context */
	result = _SPI_make_plan_non_temp(&plan);

	_SPI_end_call(true);

	return result;
}