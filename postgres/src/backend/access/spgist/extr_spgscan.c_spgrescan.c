#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int numberOfKeys; int numberOfOrderBys; TYPE_3__* orderByData; TYPE_3__* keyData; int /*<<< orphan*/  opaque; } ;
struct TYPE_12__ {int /*<<< orphan*/  fn_oid; } ;
struct TYPE_14__ {TYPE_1__ sk_func; } ;
struct TYPE_13__ {int /*<<< orphan*/ * orderByTypes; } ;
typedef  TYPE_2__* SpGistScanOpaque ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_3__* ScanKey ;
typedef  TYPE_4__* IndexScanDesc ;

/* Variables and functions */
 int /*<<< orphan*/  get_func_rettype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  resetSpGistScanOpaque (TYPE_2__*) ; 
 int /*<<< orphan*/  spgPrepareScanKeys (TYPE_4__*) ; 

void
spgrescan(IndexScanDesc scan, ScanKey scankey, int nscankeys,
		  ScanKey orderbys, int norderbys)
{
	SpGistScanOpaque so = (SpGistScanOpaque) scan->opaque;

	/* copy scankeys into local storage */
	if (scankey && scan->numberOfKeys > 0)
		memmove(scan->keyData, scankey,
				scan->numberOfKeys * sizeof(ScanKeyData));

	/* initialize order-by data if needed */
	if (orderbys && scan->numberOfOrderBys > 0)
	{
		int			i;

		memmove(scan->orderByData, orderbys,
				scan->numberOfOrderBys * sizeof(ScanKeyData));

		for (i = 0; i < scan->numberOfOrderBys; i++)
		{
			ScanKey		skey = &scan->orderByData[i];

			/*
			 * Look up the datatype returned by the original ordering
			 * operator. SP-GiST always uses a float8 for the distance
			 * function, but the ordering operator could be anything else.
			 *
			 * XXX: The distance function is only allowed to be lossy if the
			 * ordering operator's result type is float4 or float8.  Otherwise
			 * we don't know how to return the distance to the executor.  But
			 * we cannot check that here, as we won't know if the distance
			 * function is lossy until it returns *recheck = true for the
			 * first time.
			 */
			so->orderByTypes[i] = get_func_rettype(skey->sk_func.fn_oid);
		}
	}

	/* preprocess scankeys, set up the representation in *so */
	spgPrepareScanKeys(scan);

	/* set up starting queue entries */
	resetSpGistScanOpaque(so);
}