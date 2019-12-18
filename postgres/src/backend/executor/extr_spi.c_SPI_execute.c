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
struct TYPE_5__ {int /*<<< orphan*/  cursor_options; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ _SPI_plan ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_OPT_PARALLEL_OK ; 
 int /*<<< orphan*/  InvalidSnapshot ; 
 int SPI_ERROR_ARGUMENT ; 
 int /*<<< orphan*/  _SPI_PLAN_MAGIC ; 
 int _SPI_begin_call (int) ; 
 int /*<<< orphan*/  _SPI_end_call (int) ; 
 int _SPI_execute_plan (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,long) ; 
 int /*<<< orphan*/  _SPI_prepare_oneshot_plan (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int
SPI_execute(const char *src, bool read_only, long tcount)
{
	_SPI_plan	plan;
	int			res;

	if (src == NULL || tcount < 0)
		return SPI_ERROR_ARGUMENT;

	res = _SPI_begin_call(true);
	if (res < 0)
		return res;

	memset(&plan, 0, sizeof(_SPI_plan));
	plan.magic = _SPI_PLAN_MAGIC;
	plan.cursor_options = CURSOR_OPT_PARALLEL_OK;

	_SPI_prepare_oneshot_plan(src, &plan);

	res = _SPI_execute_plan(&plan, NULL,
							InvalidSnapshot, InvalidSnapshot,
							read_only, true, tcount);

	_SPI_end_call(true);
	return res;
}