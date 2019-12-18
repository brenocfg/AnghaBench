#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  argtypes; int /*<<< orphan*/  nargs; } ;
typedef  TYPE_1__* SPIPlanPtr ;
typedef  int /*<<< orphan*/  Portal ;
typedef  scalar_t__ ParamListInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_cursor_open_internal (char const*,TYPE_1__*,scalar_t__,int) ; 
 scalar_t__ _SPI_convert_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pfree (scalar_t__) ; 

Portal
SPI_cursor_open(const char *name, SPIPlanPtr plan,
				Datum *Values, const char *Nulls,
				bool read_only)
{
	Portal		portal;
	ParamListInfo paramLI;

	/* build transient ParamListInfo in caller's context */
	paramLI = _SPI_convert_params(plan->nargs, plan->argtypes,
								  Values, Nulls);

	portal = SPI_cursor_open_internal(name, plan, paramLI, read_only);

	/* done with the transient ParamListInfo */
	if (paramLI)
		pfree(paramLI);

	return portal;
}