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
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_8__ {int nlocks; int /*<<< orphan*/  filearr; int /*<<< orphan*/  snapshotarr; int /*<<< orphan*/  tupdescarr; int /*<<< orphan*/  planrefarr; int /*<<< orphan*/  catlistrefarr; int /*<<< orphan*/  catrefarr; int /*<<< orphan*/ ** locks; int /*<<< orphan*/ * parent; int /*<<< orphan*/  jitarr; int /*<<< orphan*/  dsmarr; int /*<<< orphan*/  relrefarr; int /*<<< orphan*/  bufferarr; struct TYPE_8__* nextchild; struct TYPE_8__* firstchild; } ;
struct TYPE_7__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;struct TYPE_7__* next; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  ResourceReleasePhase ;
typedef  TYPE_1__ ResourceReleaseCallbackItem ;
typedef  TYPE_2__* ResourceOwner ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  LOCALLOCK ;
typedef  int /*<<< orphan*/  JitContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  File ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  CatCList ;
typedef  int /*<<< orphan*/  CachedPlan ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 TYPE_2__* CurrentResourceOwner ; 
 int /*<<< orphan*/  DatumGetBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetFile (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DecrTupleDescRefCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockReassignCurrentOwner (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  LockReleaseCurrentOwner (int /*<<< orphan*/ **,int) ; 
 int MAX_RESOWNER_LOCKS ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintBufferLeakWarning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintCatCacheLeakWarning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintCatCacheListLeakWarning (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintDSMLeakWarning (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintFileLeakWarning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintPlanCacheLeakWarning (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintRelCacheLeakWarning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintSnapshotLeakWarning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintTupleDescLeakWarning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ProcReleaseLocks (int) ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_AFTER_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_BEFORE_LOCKS ; 
 int /*<<< orphan*/  RESOURCE_RELEASE_LOCKS ; 
 int /*<<< orphan*/  RelationClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCachedPlan (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReleaseCatCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCatCacheList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleasePredicateLocks (int,int) ; 
 scalar_t__ ResourceArrayGetAny (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ResourceRelease_callbacks ; 
 TYPE_2__* TopTransactionResourceOwner ; 
 int /*<<< orphan*/  UnregisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jit_release_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ResourceOwnerReleaseInternal(ResourceOwner owner,
							 ResourceReleasePhase phase,
							 bool isCommit,
							 bool isTopLevel)
{
	ResourceOwner child;
	ResourceOwner save;
	ResourceReleaseCallbackItem *item;
	Datum		foundres;

	/* Recurse to handle descendants */
	for (child = owner->firstchild; child != NULL; child = child->nextchild)
		ResourceOwnerReleaseInternal(child, phase, isCommit, isTopLevel);

	/*
	 * Make CurrentResourceOwner point to me, so that ReleaseBuffer etc don't
	 * get confused.
	 */
	save = CurrentResourceOwner;
	CurrentResourceOwner = owner;

	if (phase == RESOURCE_RELEASE_BEFORE_LOCKS)
	{
		/*
		 * Release buffer pins.  Note that ReleaseBuffer will remove the
		 * buffer entry from our array, so we just have to iterate till there
		 * are none.
		 *
		 * During a commit, there shouldn't be any remaining pins --- that
		 * would indicate failure to clean up the executor correctly --- so
		 * issue warnings.  In the abort case, just clean up quietly.
		 */
		while (ResourceArrayGetAny(&(owner->bufferarr), &foundres))
		{
			Buffer		res = DatumGetBuffer(foundres);

			if (isCommit)
				PrintBufferLeakWarning(res);
			ReleaseBuffer(res);
		}

		/* Ditto for relcache references */
		while (ResourceArrayGetAny(&(owner->relrefarr), &foundres))
		{
			Relation	res = (Relation) DatumGetPointer(foundres);

			if (isCommit)
				PrintRelCacheLeakWarning(res);
			RelationClose(res);
		}

		/* Ditto for dynamic shared memory segments */
		while (ResourceArrayGetAny(&(owner->dsmarr), &foundres))
		{
			dsm_segment *res = (dsm_segment *) DatumGetPointer(foundres);

			if (isCommit)
				PrintDSMLeakWarning(res);
			dsm_detach(res);
		}

		/* Ditto for JIT contexts */
		while (ResourceArrayGetAny(&(owner->jitarr), &foundres))
		{
			JitContext *context = (JitContext *) PointerGetDatum(foundres);

			jit_release_context(context);
		}
	}
	else if (phase == RESOURCE_RELEASE_LOCKS)
	{
		if (isTopLevel)
		{
			/*
			 * For a top-level xact we are going to release all locks (or at
			 * least all non-session locks), so just do a single lmgr call at
			 * the top of the recursion.
			 */
			if (owner == TopTransactionResourceOwner)
			{
				ProcReleaseLocks(isCommit);
				ReleasePredicateLocks(isCommit, false);
			}
		}
		else
		{
			/*
			 * Release locks retail.  Note that if we are committing a
			 * subtransaction, we do NOT release its locks yet, but transfer
			 * them to the parent.
			 */
			LOCALLOCK **locks;
			int			nlocks;

			Assert(owner->parent != NULL);

			/*
			 * Pass the list of locks owned by this resource owner to the lock
			 * manager, unless it has overflowed.
			 */
			if (owner->nlocks > MAX_RESOWNER_LOCKS)
			{
				locks = NULL;
				nlocks = 0;
			}
			else
			{
				locks = owner->locks;
				nlocks = owner->nlocks;
			}

			if (isCommit)
				LockReassignCurrentOwner(locks, nlocks);
			else
				LockReleaseCurrentOwner(locks, nlocks);
		}
	}
	else if (phase == RESOURCE_RELEASE_AFTER_LOCKS)
	{
		/*
		 * Release catcache references.  Note that ReleaseCatCache will remove
		 * the catref entry from our array, so we just have to iterate till
		 * there are none.
		 *
		 * As with buffer pins, warn if any are left at commit time.
		 */
		while (ResourceArrayGetAny(&(owner->catrefarr), &foundres))
		{
			HeapTuple	res = (HeapTuple) DatumGetPointer(foundres);

			if (isCommit)
				PrintCatCacheLeakWarning(res);
			ReleaseCatCache(res);
		}

		/* Ditto for catcache lists */
		while (ResourceArrayGetAny(&(owner->catlistrefarr), &foundres))
		{
			CatCList   *res = (CatCList *) DatumGetPointer(foundres);

			if (isCommit)
				PrintCatCacheListLeakWarning(res);
			ReleaseCatCacheList(res);
		}

		/* Ditto for plancache references */
		while (ResourceArrayGetAny(&(owner->planrefarr), &foundres))
		{
			CachedPlan *res = (CachedPlan *) DatumGetPointer(foundres);

			if (isCommit)
				PrintPlanCacheLeakWarning(res);
			ReleaseCachedPlan(res, true);
		}

		/* Ditto for tupdesc references */
		while (ResourceArrayGetAny(&(owner->tupdescarr), &foundres))
		{
			TupleDesc	res = (TupleDesc) DatumGetPointer(foundres);

			if (isCommit)
				PrintTupleDescLeakWarning(res);
			DecrTupleDescRefCount(res);
		}

		/* Ditto for snapshot references */
		while (ResourceArrayGetAny(&(owner->snapshotarr), &foundres))
		{
			Snapshot	res = (Snapshot) DatumGetPointer(foundres);

			if (isCommit)
				PrintSnapshotLeakWarning(res);
			UnregisterSnapshot(res);
		}

		/* Ditto for temporary files */
		while (ResourceArrayGetAny(&(owner->filearr), &foundres))
		{
			File		res = DatumGetFile(foundres);

			if (isCommit)
				PrintFileLeakWarning(res);
			FileClose(res);
		}
	}

	/* Let add-on modules get a chance too */
	for (item = ResourceRelease_callbacks; item; item = item->next)
		item->callback(phase, isCommit, isTopLevel, item->arg);

	CurrentResourceOwner = save;
}