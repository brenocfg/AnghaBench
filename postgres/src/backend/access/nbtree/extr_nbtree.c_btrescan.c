#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ numKilled; int markItemIndex; char* currTuples; char* markTuples; scalar_t__ numberOfKeys; int /*<<< orphan*/  markPos; scalar_t__ arrayKeyCount; int /*<<< orphan*/  currPos; } ;
struct TYPE_6__ {int numberOfKeys; int /*<<< orphan*/  keyData; scalar_t__ xs_want_itup; int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  ScanKey ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  TYPE_2__* BTScanOpaque ;

/* Variables and functions */
 int BLCKSZ ; 
 int /*<<< orphan*/  BTScanPosInvalidate (int /*<<< orphan*/ ) ; 
 scalar_t__ BTScanPosIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTScanPosUnpinIfPinned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_killitems (TYPE_1__*) ; 
 int /*<<< orphan*/  _bt_preprocess_array_keys (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ palloc (int) ; 

void
btrescan(IndexScanDesc scan, ScanKey scankey, int nscankeys,
		 ScanKey orderbys, int norderbys)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;

	/* we aren't holding any read locks, but gotta drop the pins */
	if (BTScanPosIsValid(so->currPos))
	{
		/* Before leaving current page, deal with any killed items */
		if (so->numKilled > 0)
			_bt_killitems(scan);
		BTScanPosUnpinIfPinned(so->currPos);
		BTScanPosInvalidate(so->currPos);
	}

	so->markItemIndex = -1;
	so->arrayKeyCount = 0;
	BTScanPosUnpinIfPinned(so->markPos);
	BTScanPosInvalidate(so->markPos);

	/*
	 * Allocate tuple workspace arrays, if needed for an index-only scan and
	 * not already done in a previous rescan call.  To save on palloc
	 * overhead, both workspaces are allocated as one palloc block; only this
	 * function and btendscan know that.
	 *
	 * NOTE: this data structure also makes it safe to return data from a
	 * "name" column, even though btree name_ops uses an underlying storage
	 * datatype of cstring.  The risk there is that "name" is supposed to be
	 * padded to NAMEDATALEN, but the actual index tuple is probably shorter.
	 * However, since we only return data out of tuples sitting in the
	 * currTuples array, a fetch of NAMEDATALEN bytes can at worst pull some
	 * data out of the markTuples array --- running off the end of memory for
	 * a SIGSEGV is not possible.  Yeah, this is ugly as sin, but it beats
	 * adding special-case treatment for name_ops elsewhere.
	 */
	if (scan->xs_want_itup && so->currTuples == NULL)
	{
		so->currTuples = (char *) palloc(BLCKSZ * 2);
		so->markTuples = so->currTuples + BLCKSZ;
	}

	/*
	 * Reset the scan keys. Note that keys ordering stuff moved to _bt_first.
	 * - vadim 05/05/97
	 */
	if (scankey && scan->numberOfKeys > 0)
		memmove(scan->keyData,
				scankey,
				scan->numberOfKeys * sizeof(ScanKeyData));
	so->numberOfKeys = 0;		/* until _bt_preprocess_keys sets it */

	/* If any keys are SK_SEARCHARRAY type, set up array-key info */
	_bt_preprocess_array_keys(scan);
}