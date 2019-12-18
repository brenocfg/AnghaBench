#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t scan_key; scalar_t__ num_elems; size_t cur_elem; int /*<<< orphan*/ * elem_values; } ;
struct TYPE_8__ {int numArrayKeys; TYPE_1__* arrayKeyData; TYPE_4__* arrayKeys; } ;
struct TYPE_7__ {int /*<<< orphan*/  opaque; } ;
struct TYPE_6__ {int /*<<< orphan*/  sk_argument; } ;
typedef  TYPE_1__* ScanKey ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_2__* IndexScanDesc ;
typedef  TYPE_3__* BTScanOpaque ;
typedef  TYPE_4__ BTArrayKeyInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ ScanDirectionIsBackward (int /*<<< orphan*/ ) ; 

void
_bt_start_array_keys(IndexScanDesc scan, ScanDirection dir)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;
	int			i;

	for (i = 0; i < so->numArrayKeys; i++)
	{
		BTArrayKeyInfo *curArrayKey = &so->arrayKeys[i];
		ScanKey		skey = &so->arrayKeyData[curArrayKey->scan_key];

		Assert(curArrayKey->num_elems > 0);
		if (ScanDirectionIsBackward(dir))
			curArrayKey->cur_elem = curArrayKey->num_elems - 1;
		else
			curArrayKey->cur_elem = 0;
		skey->sk_argument = curArrayKey->elem_values[curArrayKey->cur_elem];
	}
}