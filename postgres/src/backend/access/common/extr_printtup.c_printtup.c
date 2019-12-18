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
typedef  int /*<<< orphan*/  bytea ;
struct TYPE_9__ {scalar_t__* tts_isnull; int /*<<< orphan*/ * tts_values; TYPE_2__* tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_12__ {int nattrs; int /*<<< orphan*/  tmpcontext; TYPE_3__* myinfo; TYPE_2__* attrinfo; int /*<<< orphan*/  buf; } ;
struct TYPE_11__ {scalar_t__ format; int /*<<< orphan*/  finfo; scalar_t__ typisvarlena; } ;
struct TYPE_10__ {int natts; } ;
typedef  int /*<<< orphan*/ * StringInfo ;
typedef  TYPE_3__ PrinttupAttrInfo ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__ DR_printtup ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 char* OutputFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SendFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALGRIND_CHECK_MEM_IS_DEFINED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARDATA (int /*<<< orphan*/ *) ; 
 int VARHDRSZ ; 
 int VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_beginmessage_reuse (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage_reuse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendbytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_sendcountedtext (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_sendint16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printtup_prepare_info (TYPE_4__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  slot_getallattrs (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static bool
printtup(TupleTableSlot *slot, DestReceiver *self)
{
	TupleDesc	typeinfo = slot->tts_tupleDescriptor;
	DR_printtup *myState = (DR_printtup *) self;
	MemoryContext oldcontext;
	StringInfo	buf = &myState->buf;
	int			natts = typeinfo->natts;
	int			i;

	/* Set or update my derived attribute info, if needed */
	if (myState->attrinfo != typeinfo || myState->nattrs != natts)
		printtup_prepare_info(myState, typeinfo, natts);

	/* Make sure the tuple is fully deconstructed */
	slot_getallattrs(slot);

	/* Switch into per-row context so we can recover memory below */
	oldcontext = MemoryContextSwitchTo(myState->tmpcontext);

	/*
	 * Prepare a DataRow message (note buffer is in per-row context)
	 */
	pq_beginmessage_reuse(buf, 'D');

	pq_sendint16(buf, natts);

	/*
	 * send the attributes of this tuple
	 */
	for (i = 0; i < natts; ++i)
	{
		PrinttupAttrInfo *thisState = myState->myinfo + i;
		Datum		attr = slot->tts_values[i];

		if (slot->tts_isnull[i])
		{
			pq_sendint32(buf, -1);
			continue;
		}

		/*
		 * Here we catch undefined bytes in datums that are returned to the
		 * client without hitting disk; see comments at the related check in
		 * PageAddItem().  This test is most useful for uncompressed,
		 * non-external datums, but we're quite likely to see such here when
		 * testing new C functions.
		 */
		if (thisState->typisvarlena)
			VALGRIND_CHECK_MEM_IS_DEFINED(DatumGetPointer(attr),
										  VARSIZE_ANY(attr));

		if (thisState->format == 0)
		{
			/* Text output */
			char	   *outputstr;

			outputstr = OutputFunctionCall(&thisState->finfo, attr);
			pq_sendcountedtext(buf, outputstr, strlen(outputstr), false);
		}
		else
		{
			/* Binary output */
			bytea	   *outputbytes;

			outputbytes = SendFunctionCall(&thisState->finfo, attr);
			pq_sendint32(buf, VARSIZE(outputbytes) - VARHDRSZ);
			pq_sendbytes(buf, VARDATA(outputbytes),
						 VARSIZE(outputbytes) - VARHDRSZ);
		}
	}

	pq_endmessage_reuse(buf);

	/* Return to caller's context, and flush row's temporary memory */
	MemoryContextSwitchTo(oldcontext);
	MemoryContextReset(myState->tmpcontext);

	return true;
}