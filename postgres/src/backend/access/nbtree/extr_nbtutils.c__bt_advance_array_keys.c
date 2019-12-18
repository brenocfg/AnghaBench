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
struct TYPE_10__ {size_t scan_key; int cur_elem; int num_elems; int /*<<< orphan*/ * elem_values; } ;
struct TYPE_9__ {int numArrayKeys; TYPE_1__* arrayKeyData; TYPE_4__* arrayKeys; } ;
struct TYPE_8__ {int /*<<< orphan*/ * parallel_scan; int /*<<< orphan*/  opaque; } ;
struct TYPE_7__ {int /*<<< orphan*/  sk_argument; } ;
typedef  TYPE_1__* ScanKey ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  TYPE_3__* BTScanOpaque ;
typedef  TYPE_4__ BTArrayKeyInfo ;

/* Variables and functions */
 scalar_t__ ScanDirectionIsBackward (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_parallel_advance_array_keys (TYPE_2__*) ; 

bool
_bt_advance_array_keys(IndexScanDesc scan, ScanDirection dir)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	bool		found = false;
	int			i;

	/*
	 * We must advance the last array key most quickly, since it will
	 * correspond to the lowest-order index column among the available
	 * qualifications. This is necessary to ensure correct ordering of output
	 * when there are multiple array keys.
	 */
	for (i = so->numArrayKeys - 1; i >= 0; i--)
	{
		BTArrayKeyInfo *curArrayKey = &so->arrayKeys[i];
		ScanKey		skey = &so->arrayKeyData[curArrayKey->scan_key];
		int			cur_elem = curArrayKey->cur_elem;
		int			num_elems = curArrayKey->num_elems;

		if (ScanDirectionIsBackward(dir))
		{
			if (--cur_elem < 0)
			{
				cur_elem = num_elems - 1;
				found = false;	/* need to advance next array key */
			}
			else
				found = true;
		}
		else
		{
			if (++cur_elem >= num_elems)
			{
				cur_elem = 0;
				found = false;	/* need to advance next array key */
			}
			else
				found = true;
		}

		curArrayKey->cur_elem = cur_elem;
		skey->sk_argument = curArrayKey->elem_values[cur_elem];
		if (found)
			break;
	}

	/* advance parallel scan */
	if (scan->parallel_scan != NULL)
		_bt_parallel_advance_array_keys(scan);

	return found;
}