#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hash_ctl ;
struct TYPE_12__ {int /*<<< orphan*/  const* inforec; int /*<<< orphan*/  user_fn; int /*<<< orphan*/  fn_tid; int /*<<< orphan*/  fn_xmin; } ;
struct TYPE_11__ {int /*<<< orphan*/  oid; } ;
struct TYPE_10__ {int keysize; int entrysize; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_self; int /*<<< orphan*/  t_data; } ;
typedef  int /*<<< orphan*/  Pg_finfo_record ;
typedef  int /*<<< orphan*/  PGFunction ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__ HASHCTL ;
typedef  TYPE_3__* Form_pg_proc ;
typedef  TYPE_4__ CFuncHashTabEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * CFuncHash ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HeapTupleHeaderGetRawXmin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_2__*,int) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
record_C_func(HeapTuple procedureTuple,
			  PGFunction user_fn, const Pg_finfo_record *inforec)
{
	Oid			fn_oid = ((Form_pg_proc) GETSTRUCT(procedureTuple))->oid;
	CFuncHashTabEntry *entry;
	bool		found;

	/* Create the hash table if it doesn't exist yet */
	if (CFuncHash == NULL)
	{
		HASHCTL		hash_ctl;

		MemSet(&hash_ctl, 0, sizeof(hash_ctl));
		hash_ctl.keysize = sizeof(Oid);
		hash_ctl.entrysize = sizeof(CFuncHashTabEntry);
		CFuncHash = hash_create("CFuncHash",
								100,
								&hash_ctl,
								HASH_ELEM | HASH_BLOBS);
	}

	entry = (CFuncHashTabEntry *)
		hash_search(CFuncHash,
					&fn_oid,
					HASH_ENTER,
					&found);
	/* OID is already filled in */
	entry->fn_xmin = HeapTupleHeaderGetRawXmin(procedureTuple->t_data);
	entry->fn_tid = procedureTuple->t_self;
	entry->user_fn = user_fn;
	entry->inforec = inforec;
}