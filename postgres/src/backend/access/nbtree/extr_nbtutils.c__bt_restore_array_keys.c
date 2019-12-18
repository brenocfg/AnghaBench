#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t scan_key; int mark_elem; int cur_elem; int /*<<< orphan*/ * elem_values; } ;
struct TYPE_9__ {int numArrayKeys; int /*<<< orphan*/  qual_ok; TYPE_1__* arrayKeyData; TYPE_4__* arrayKeys; } ;
struct TYPE_8__ {int /*<<< orphan*/  opaque; } ;
struct TYPE_7__ {int /*<<< orphan*/  sk_argument; } ;
typedef  TYPE_1__* ScanKey ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  TYPE_3__* BTScanOpaque ;
typedef  TYPE_4__ BTArrayKeyInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_preprocess_keys (TYPE_2__*) ; 

void
_bt_restore_array_keys(IndexScanDesc scan)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	bool		changed = false;
	int			i;

	/* Restore each array key to its position when the mark was set */
	for (i = 0; i < so->numArrayKeys; i++)
	{
		BTArrayKeyInfo *curArrayKey = &so->arrayKeys[i];
		ScanKey		skey = &so->arrayKeyData[curArrayKey->scan_key];
		int			mark_elem = curArrayKey->mark_elem;

		if (curArrayKey->cur_elem != mark_elem)
		{
			curArrayKey->cur_elem = mark_elem;
			skey->sk_argument = curArrayKey->elem_values[mark_elem];
			changed = true;
		}
	}

	/*
	 * If we changed any keys, we must redo _bt_preprocess_keys.  That might
	 * sound like overkill, but in cases with multiple keys per index column
	 * it seems necessary to do the full set of pushups.
	 */
	if (changed)
	{
		_bt_preprocess_keys(scan);
		/* The mark should have been set on a consistent set of keys... */
		Assert(so->qual_ok);
	}
}