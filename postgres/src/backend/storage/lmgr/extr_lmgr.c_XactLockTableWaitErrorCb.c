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
struct TYPE_2__ {int oper; int /*<<< orphan*/  rel; int /*<<< orphan*/  ctid; } ;
typedef  TYPE_1__ XactLockTableWaitInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ItemPointerGetBlockNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ItemPointerGetOffsetNumber (int /*<<< orphan*/ ) ; 
 scalar_t__ ItemPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationIsValid (int /*<<< orphan*/ ) ; 
#define  XLTW_Delete 135 
#define  XLTW_FetchUpdated 134 
#define  XLTW_InsertIndex 133 
#define  XLTW_InsertIndexUnique 132 
#define  XLTW_Lock 131 
#define  XLTW_LockUpdated 130 
 int XLTW_None ; 
#define  XLTW_RecheckExclusionConstr 129 
#define  XLTW_Update 128 
 int /*<<< orphan*/  errcontext (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* gettext_noop (char*) ; 

__attribute__((used)) static void
XactLockTableWaitErrorCb(void *arg)
{
	XactLockTableWaitInfo *info = (XactLockTableWaitInfo *) arg;

	/*
	 * We would like to print schema name too, but that would require a
	 * syscache lookup.
	 */
	if (info->oper != XLTW_None &&
		ItemPointerIsValid(info->ctid) && RelationIsValid(info->rel))
	{
		const char *cxt;

		switch (info->oper)
		{
			case XLTW_Update:
				cxt = gettext_noop("while updating tuple (%u,%u) in relation \"%s\"");
				break;
			case XLTW_Delete:
				cxt = gettext_noop("while deleting tuple (%u,%u) in relation \"%s\"");
				break;
			case XLTW_Lock:
				cxt = gettext_noop("while locking tuple (%u,%u) in relation \"%s\"");
				break;
			case XLTW_LockUpdated:
				cxt = gettext_noop("while locking updated version (%u,%u) of tuple in relation \"%s\"");
				break;
			case XLTW_InsertIndex:
				cxt = gettext_noop("while inserting index tuple (%u,%u) in relation \"%s\"");
				break;
			case XLTW_InsertIndexUnique:
				cxt = gettext_noop("while checking uniqueness of tuple (%u,%u) in relation \"%s\"");
				break;
			case XLTW_FetchUpdated:
				cxt = gettext_noop("while rechecking updated tuple (%u,%u) in relation \"%s\"");
				break;
			case XLTW_RecheckExclusionConstr:
				cxt = gettext_noop("while checking exclusion constraint on tuple (%u,%u) in relation \"%s\"");
				break;

			default:
				return;
		}

		errcontext(cxt,
				   ItemPointerGetBlockNumber(info->ctid),
				   ItemPointerGetOffsetNumber(info->ctid),
				   RelationGetRelationName(info->rel));
	}
}