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
struct TYPE_5__ {int atomic; int internal_xact; int /*<<< orphan*/ * procCxt; int /*<<< orphan*/  savedcxt; int /*<<< orphan*/ * execCxt; scalar_t__ outer_result; int /*<<< orphan*/ * outer_tuptable; scalar_t__ outer_processed; int /*<<< orphan*/ * queryEnv; int /*<<< orphan*/  connectSubid; int /*<<< orphan*/  tuptables; int /*<<< orphan*/  execSubid; int /*<<< orphan*/ * tuptable; scalar_t__ processed; } ;
typedef  TYPE_1__ _SPI_connection ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 void* AllocSetContextCreate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 int /*<<< orphan*/  InvalidSubTransactionId ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PortalContext ; 
 int SPI_OK_CONNECT ; 
 int SPI_OPT_NONATOMIC ; 
 scalar_t__ SPI_processed ; 
 scalar_t__ SPI_result ; 
 int /*<<< orphan*/ * SPI_tuptable ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/ * TopTransactionContext ; 
 int _SPI_connected ; 
 TYPE_1__* _SPI_current ; 
 TYPE_1__* _SPI_stack ; 
 int _SPI_stack_depth ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ repalloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  slist_init (int /*<<< orphan*/ *) ; 

int
SPI_connect_ext(int options)
{
	int			newdepth;

	/* Enlarge stack if necessary */
	if (_SPI_stack == NULL)
	{
		if (_SPI_connected != -1 || _SPI_stack_depth != 0)
			elog(ERROR, "SPI stack corrupted");
		newdepth = 16;
		_SPI_stack = (_SPI_connection *)
			MemoryContextAlloc(TopMemoryContext,
							   newdepth * sizeof(_SPI_connection));
		_SPI_stack_depth = newdepth;
	}
	else
	{
		if (_SPI_stack_depth <= 0 || _SPI_stack_depth <= _SPI_connected)
			elog(ERROR, "SPI stack corrupted");
		if (_SPI_stack_depth == _SPI_connected + 1)
		{
			newdepth = _SPI_stack_depth * 2;
			_SPI_stack = (_SPI_connection *)
				repalloc(_SPI_stack,
						 newdepth * sizeof(_SPI_connection));
			_SPI_stack_depth = newdepth;
		}
	}

	/* Enter new stack level */
	_SPI_connected++;
	Assert(_SPI_connected >= 0 && _SPI_connected < _SPI_stack_depth);

	_SPI_current = &(_SPI_stack[_SPI_connected]);
	_SPI_current->processed = 0;
	_SPI_current->tuptable = NULL;
	_SPI_current->execSubid = InvalidSubTransactionId;
	slist_init(&_SPI_current->tuptables);
	_SPI_current->procCxt = NULL;	/* in case we fail to create 'em */
	_SPI_current->execCxt = NULL;
	_SPI_current->connectSubid = GetCurrentSubTransactionId();
	_SPI_current->queryEnv = NULL;
	_SPI_current->atomic = (options & SPI_OPT_NONATOMIC ? false : true);
	_SPI_current->internal_xact = false;
	_SPI_current->outer_processed = SPI_processed;
	_SPI_current->outer_tuptable = SPI_tuptable;
	_SPI_current->outer_result = SPI_result;

	/*
	 * Create memory contexts for this procedure
	 *
	 * In atomic contexts (the normal case), we use TopTransactionContext,
	 * otherwise PortalContext, so that it lives across transaction
	 * boundaries.
	 *
	 * XXX It could be better to use PortalContext as the parent context in
	 * all cases, but we may not be inside a portal (consider deferred-trigger
	 * execution).  Perhaps CurTransactionContext could be an option?  For now
	 * it doesn't matter because we clean up explicitly in AtEOSubXact_SPI().
	 */
	_SPI_current->procCxt = AllocSetContextCreate(_SPI_current->atomic ? TopTransactionContext : PortalContext,
												  "SPI Proc",
												  ALLOCSET_DEFAULT_SIZES);
	_SPI_current->execCxt = AllocSetContextCreate(_SPI_current->atomic ? TopTransactionContext : _SPI_current->procCxt,
												  "SPI Exec",
												  ALLOCSET_DEFAULT_SIZES);
	/* ... and switch to procedure's context */
	_SPI_current->savedcxt = MemoryContextSwitchTo(_SPI_current->procCxt);

	/*
	 * Reset API global variables so that current caller cannot accidentally
	 * depend on state of an outer caller.
	 */
	SPI_processed = 0;
	SPI_tuptable = NULL;
	SPI_result = 0;

	return SPI_OK_CONNECT;
}