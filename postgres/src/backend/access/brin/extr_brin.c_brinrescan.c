#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numberOfKeys; int /*<<< orphan*/  keyData; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  scalar_t__ ScanKey ;
typedef  TYPE_1__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
brinrescan(IndexScanDesc scan, ScanKey scankey, int nscankeys,
		   ScanKey orderbys, int norderbys)
{
	/*
	 * Other index AMs preprocess the scan keys at this point, or sometime
	 * early during the scan; this lets them optimize by removing redundant
	 * keys, or doing early returns when they are impossible to satisfy; see
	 * _bt_preprocess_keys for an example.  Something like that could be added
	 * here someday, too.
	 */

	if (scankey && scan->numberOfKeys > 0)
		memmove(scan->keyData, scankey,
				scan->numberOfKeys * sizeof(ScanKeyData));
}