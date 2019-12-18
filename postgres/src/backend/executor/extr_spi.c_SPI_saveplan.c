#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ magic; } ;
typedef  TYPE_1__* SPIPlanPtr ;

/* Variables and functions */
 scalar_t__ SPI_ERROR_ARGUMENT ; 
 scalar_t__ SPI_result ; 
 scalar_t__ _SPI_PLAN_MAGIC ; 
 scalar_t__ _SPI_begin_call (int) ; 
 scalar_t__ _SPI_end_call (int) ; 
 TYPE_1__* _SPI_save_plan (TYPE_1__*) ; 

SPIPlanPtr
SPI_saveplan(SPIPlanPtr plan)
{
	SPIPlanPtr	newplan;

	if (plan == NULL || plan->magic != _SPI_PLAN_MAGIC)
	{
		SPI_result = SPI_ERROR_ARGUMENT;
		return NULL;
	}

	SPI_result = _SPI_begin_call(false);	/* don't change context */
	if (SPI_result < 0)
		return NULL;

	newplan = _SPI_save_plan(plan);

	SPI_result = _SPI_end_call(false);

	return newplan;
}