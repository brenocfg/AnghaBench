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
struct TYPE_8__ {int /*<<< orphan*/  currPos; } ;
struct TYPE_7__ {int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  ScanDirection ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  int /*<<< orphan*/  BlockNumber ;
typedef  TYPE_2__* BTScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  _bt_drop_lock_and_maybe_pin (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bt_initialize_more_data (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bt_readnextpage (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
_bt_parallel_readpage(IndexScanDesc scan, BlockNumber blkno, ScanDirection dir)
{
	BTScanOpaque so = (BTScanOpaque) scan->opaque;

	_bt_initialize_more_data(so, dir);

	if (!_bt_readnextpage(scan, blkno, dir))
		return false;

	/* Drop the lock, and maybe the pin, on the current page */
	_bt_drop_lock_and_maybe_pin(scan, &so->currPos);

	return true;
}