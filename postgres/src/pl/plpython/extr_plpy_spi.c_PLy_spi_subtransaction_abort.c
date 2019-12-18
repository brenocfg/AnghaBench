#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sqlerrcode; } ;
struct TYPE_7__ {int /*<<< orphan*/ * exc; } ;
typedef  int /*<<< orphan*/  ResourceOwner ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ PLyExceptionEntry ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ ErrorData ;

/* Variables and functions */
 TYPE_2__* CopyErrorData () ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  FlushErrorState () ; 
 int /*<<< orphan*/  FreeErrorData (TYPE_2__*) ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PLy_exc_spi_error ; 
 int /*<<< orphan*/  PLy_spi_exception_set (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  PLy_spi_exceptions ; 
 int /*<<< orphan*/  RollbackAndReleaseCurrentSubTransaction () ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
PLy_spi_subtransaction_abort(MemoryContext oldcontext, ResourceOwner oldowner)
{
	ErrorData  *edata;
	PLyExceptionEntry *entry;
	PyObject   *exc;

	/* Save error info */
	MemoryContextSwitchTo(oldcontext);
	edata = CopyErrorData();
	FlushErrorState();

	/* Abort the inner transaction */
	RollbackAndReleaseCurrentSubTransaction();
	MemoryContextSwitchTo(oldcontext);
	CurrentResourceOwner = oldowner;

	/* Look up the correct exception */
	entry = hash_search(PLy_spi_exceptions, &(edata->sqlerrcode),
						HASH_FIND, NULL);

	/*
	 * This could be a custom error code, if that's the case fallback to
	 * SPIError
	 */
	exc = entry ? entry->exc : PLy_exc_spi_error;
	/* Make Python raise the exception */
	PLy_spi_exception_set(exc, edata);
	FreeErrorData(edata);
}