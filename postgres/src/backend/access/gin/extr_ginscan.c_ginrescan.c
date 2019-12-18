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
struct TYPE_3__ {int numberOfKeys; int /*<<< orphan*/  keyData; int /*<<< orphan*/  opaque; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  scalar_t__ ScanKey ;
typedef  TYPE_1__* IndexScanDesc ;
typedef  int /*<<< orphan*/  GinScanOpaque ;

/* Variables and functions */
 int /*<<< orphan*/  ginFreeScanKeys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
ginrescan(IndexScanDesc scan, ScanKey scankey, int nscankeys,
		  ScanKey orderbys, int norderbys)
{
	GinScanOpaque so = (GinScanOpaque) scan->opaque;

	ginFreeScanKeys(so);

	if (scankey && scan->numberOfKeys > 0)
	{
		memmove(scan->keyData, scankey,
				scan->numberOfKeys * sizeof(ScanKeyData));
	}
}