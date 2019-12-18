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
struct TYPE_3__ {int /*<<< orphan*/  outer_result; int /*<<< orphan*/  outer_tuptable; int /*<<< orphan*/  outer_processed; int /*<<< orphan*/ * procCxt; int /*<<< orphan*/ * execCxt; int /*<<< orphan*/  savedcxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int SPI_OK_FINISH ; 
 int /*<<< orphan*/  SPI_processed ; 
 int /*<<< orphan*/  SPI_result ; 
 int /*<<< orphan*/  SPI_tuptable ; 
 int _SPI_begin_call (int) ; 
 size_t _SPI_connected ; 
 TYPE_1__* _SPI_current ; 
 TYPE_1__* _SPI_stack ; 

int
SPI_finish(void)
{
	int			res;

	res = _SPI_begin_call(false);	/* just check we're connected */
	if (res < 0)
		return res;

	/* Restore memory context as it was before procedure call */
	MemoryContextSwitchTo(_SPI_current->savedcxt);

	/* Release memory used in procedure call (including tuptables) */
	MemoryContextDelete(_SPI_current->execCxt);
	_SPI_current->execCxt = NULL;
	MemoryContextDelete(_SPI_current->procCxt);
	_SPI_current->procCxt = NULL;

	/*
	 * Restore outer API variables, especially SPI_tuptable which is probably
	 * pointing at a just-deleted tuptable
	 */
	SPI_processed = _SPI_current->outer_processed;
	SPI_tuptable = _SPI_current->outer_tuptable;
	SPI_result = _SPI_current->outer_result;

	/* Exit stack level */
	_SPI_connected--;
	if (_SPI_connected < 0)
		_SPI_current = NULL;
	else
		_SPI_current = &(_SPI_stack[_SPI_connected]);

	return SPI_OK_FINISH;
}