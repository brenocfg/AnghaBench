#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_8__ {int indexsize; int t; int size; } ;
typedef  TYPE_1__ gbtree_ninfo ;
typedef  int /*<<< orphan*/  float8 ;
typedef  int /*<<< orphan*/  float4 ;
typedef  int /*<<< orphan*/  Timestamp ;
typedef  int /*<<< orphan*/  TimeADT ;
struct TYPE_9__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  page; int /*<<< orphan*/  rel; int /*<<< orphan*/  key; scalar_t__ leafkey; } ;
typedef  TYPE_2__ GISTENTRY ;
typedef  int /*<<< orphan*/  GBT_NUMKEY ;
typedef  int /*<<< orphan*/  DateADT ;
typedef  int /*<<< orphan*/  Cash ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DatumGetCash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetDateADT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetFloat4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetFloat8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetObjectId (int /*<<< orphan*/ ) ; 
 void* DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetTimeADT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetTimestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
#define  gbt_t_cash 138 
#define  gbt_t_date 137 
#define  gbt_t_enum 136 
#define  gbt_t_float4 135 
#define  gbt_t_float8 134 
#define  gbt_t_int2 133 
#define  gbt_t_int4 132 
#define  gbt_t_int8 131 
#define  gbt_t_oid 130 
#define  gbt_t_time 129 
#define  gbt_t_ts 128 
 int /*<<< orphan*/  gistentryinit (TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 TYPE_2__* palloc (int) ; 
 scalar_t__ palloc0 (int) ; 

GISTENTRY *
gbt_num_compress(GISTENTRY *entry, const gbtree_ninfo *tinfo)
{
	GISTENTRY  *retval;

	if (entry->leafkey)
	{
		union
		{
			int16		i2;
			int32		i4;
			int64		i8;
			float4		f4;
			float8		f8;
			DateADT		dt;
			TimeADT		tm;
			Timestamp	ts;
			Cash		ch;
		}			v;

		GBT_NUMKEY *r = (GBT_NUMKEY *) palloc0(tinfo->indexsize);
		void	   *leaf = NULL;

		switch (tinfo->t)
		{
			case gbt_t_int2:
				v.i2 = DatumGetInt16(entry->key);
				leaf = &v.i2;
				break;
			case gbt_t_int4:
				v.i4 = DatumGetInt32(entry->key);
				leaf = &v.i4;
				break;
			case gbt_t_int8:
				v.i8 = DatumGetInt64(entry->key);
				leaf = &v.i8;
				break;
			case gbt_t_oid:
			case gbt_t_enum:
				v.i4 = DatumGetObjectId(entry->key);
				leaf = &v.i4;
				break;
			case gbt_t_float4:
				v.f4 = DatumGetFloat4(entry->key);
				leaf = &v.f4;
				break;
			case gbt_t_float8:
				v.f8 = DatumGetFloat8(entry->key);
				leaf = &v.f8;
				break;
			case gbt_t_date:
				v.dt = DatumGetDateADT(entry->key);
				leaf = &v.dt;
				break;
			case gbt_t_time:
				v.tm = DatumGetTimeADT(entry->key);
				leaf = &v.tm;
				break;
			case gbt_t_ts:
				v.ts = DatumGetTimestamp(entry->key);
				leaf = &v.ts;
				break;
			case gbt_t_cash:
				v.ch = DatumGetCash(entry->key);
				leaf = &v.ch;
				break;
			default:
				leaf = DatumGetPointer(entry->key);
		}

		Assert(tinfo->indexsize >= 2 * tinfo->size);

		memcpy((void *) &r[0], leaf, tinfo->size);
		memcpy((void *) &r[tinfo->size], leaf, tinfo->size);
		retval = palloc(sizeof(GISTENTRY));
		gistentryinit(*retval, PointerGetDatum(r), entry->rel, entry->page,
					  entry->offset, false);
	}
	else
		retval = entry;

	return retval;
}