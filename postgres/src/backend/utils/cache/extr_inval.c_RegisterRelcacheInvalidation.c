#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int RelcacheInitFileInval; int /*<<< orphan*/  CurrentCmdInvalidMsgs; } ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AddRelcacheInvalidationMessage (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GetCurrentCommandId (int) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ RelationIdIsInInitFile (scalar_t__) ; 
 TYPE_1__* transInvalInfo ; 

__attribute__((used)) static void
RegisterRelcacheInvalidation(Oid dbId, Oid relId)
{
	AddRelcacheInvalidationMessage(&transInvalInfo->CurrentCmdInvalidMsgs,
								   dbId, relId);

	/*
	 * Most of the time, relcache invalidation is associated with system
	 * catalog updates, but there are a few cases where it isn't.  Quick hack
	 * to ensure that the next CommandCounterIncrement() will think that we
	 * need to do CommandEndInvalidationMessages().
	 */
	(void) GetCurrentCommandId(true);

	/*
	 * If the relation being invalidated is one of those cached in a relcache
	 * init file, mark that we need to zap that file at commit. For simplicity
	 * invalidations for a specific database always invalidate the shared file
	 * as well.  Also zap when we are invalidating whole relcache.
	 */
	if (relId == InvalidOid || RelationIdIsInInitFile(relId))
		transInvalInfo->RelcacheInitFileInval = true;
}