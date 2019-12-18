#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int atStart; int atEnd; int visible; int /*<<< orphan*/  name; int /*<<< orphan*/  portalContext; int /*<<< orphan*/  creation_time; int /*<<< orphan*/  cursorOptions; int /*<<< orphan*/  strategy; int /*<<< orphan*/  createSubid; int /*<<< orphan*/  activeSubid; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  status; int /*<<< orphan*/  resowner; } ;
typedef  TYPE_1__* Portal ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AssertArg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURSOR_OPT_NO_SCROLL ; 
 int /*<<< orphan*/  CurTransactionResourceOwner ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_CURSOR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentStatementStartTimestamp () ; 
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 TYPE_1__* GetPortalByName (char const*) ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSetIdentifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORTAL_MULTI_QUERY ; 
 int /*<<< orphan*/  PORTAL_NEW ; 
 int /*<<< orphan*/  PointerIsValid (char const*) ; 
 int /*<<< orphan*/  PortalCleanup ; 
 int /*<<< orphan*/  PortalDrop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  PortalHashTableInsert (TYPE_1__*,char const*) ; 
 scalar_t__ PortalIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  ResourceOwnerCreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TopPortalContext ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 

Portal
CreatePortal(const char *name, bool allowDup, bool dupSilent)
{
	Portal		portal;

	AssertArg(PointerIsValid(name));

	portal = GetPortalByName(name);
	if (PortalIsValid(portal))
	{
		if (!allowDup)
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_CURSOR),
					 errmsg("cursor \"%s\" already exists", name)));
		if (!dupSilent)
			ereport(WARNING,
					(errcode(ERRCODE_DUPLICATE_CURSOR),
					 errmsg("closing existing cursor \"%s\"",
							name)));
		PortalDrop(portal, false);
	}

	/* make new portal structure */
	portal = (Portal) MemoryContextAllocZero(TopPortalContext, sizeof *portal);

	/* initialize portal context; typically it won't store much */
	portal->portalContext = AllocSetContextCreate(TopPortalContext,
												  "PortalContext",
												  ALLOCSET_SMALL_SIZES);

	/* create a resource owner for the portal */
	portal->resowner = ResourceOwnerCreate(CurTransactionResourceOwner,
										   "Portal");

	/* initialize portal fields that don't start off zero */
	portal->status = PORTAL_NEW;
	portal->cleanup = PortalCleanup;
	portal->createSubid = GetCurrentSubTransactionId();
	portal->activeSubid = portal->createSubid;
	portal->strategy = PORTAL_MULTI_QUERY;
	portal->cursorOptions = CURSOR_OPT_NO_SCROLL;
	portal->atStart = true;
	portal->atEnd = true;		/* disallow fetches until query is set */
	portal->visible = true;
	portal->creation_time = GetCurrentStatementStartTimestamp();

	/* put portal in table (sets portal->name) */
	PortalHashTableInsert(portal, name);

	/* reuse portal->name copy */
	MemoryContextSetIdentifier(portal->portalContext, portal->name);

	return portal;
}