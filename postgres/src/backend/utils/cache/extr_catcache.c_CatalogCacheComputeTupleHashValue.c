#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_4__ {int* cc_keyno; int /*<<< orphan*/  cc_tupdesc; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_1__ CatCache ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CatalogCacheComputeHashValue (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fastgetattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static uint32
CatalogCacheComputeTupleHashValue(CatCache *cache, int nkeys, HeapTuple tuple)
{
	Datum		v1 = 0,
				v2 = 0,
				v3 = 0,
				v4 = 0;
	bool		isNull = false;
	int		   *cc_keyno = cache->cc_keyno;
	TupleDesc	cc_tupdesc = cache->cc_tupdesc;

	/* Now extract key fields from tuple, insert into scankey */
	switch (nkeys)
	{
		case 4:
			v4 = fastgetattr(tuple,
							 cc_keyno[3],
							 cc_tupdesc,
							 &isNull);
			Assert(!isNull);
			/* FALLTHROUGH */
		case 3:
			v3 = fastgetattr(tuple,
							 cc_keyno[2],
							 cc_tupdesc,
							 &isNull);
			Assert(!isNull);
			/* FALLTHROUGH */
		case 2:
			v2 = fastgetattr(tuple,
							 cc_keyno[1],
							 cc_tupdesc,
							 &isNull);
			Assert(!isNull);
			/* FALLTHROUGH */
		case 1:
			v1 = fastgetattr(tuple,
							 cc_keyno[0],
							 cc_tupdesc,
							 &isNull);
			Assert(!isNull);
			break;
		default:
			elog(FATAL, "wrong number of hash keys: %d", nkeys);
			break;
	}

	return CatalogCacheComputeHashValue(cache, nkeys, v1, v2, v3, v4);
}