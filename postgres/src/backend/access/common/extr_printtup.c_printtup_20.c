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
struct TYPE_9__ {scalar_t__* tts_isnull; int /*<<< orphan*/ * tts_values; TYPE_2__* tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_12__ {int nattrs; int /*<<< orphan*/  tmpcontext; TYPE_3__* myinfo; TYPE_2__* attrinfo; int /*<<< orphan*/  buf; } ;
struct TYPE_11__ {scalar_t__ format; int /*<<< orphan*/  finfo; } ;
struct TYPE_10__ {int natts; } ;
typedef  int /*<<< orphan*/ * StringInfo ;
typedef  TYPE_3__ PrinttupAttrInfo ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  Datum ;
typedef  TYPE_4__ DR_printtup ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 char* OutputFunctionCall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_beginmessage_reuse (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage_reuse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendcountedtext (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_sendint8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printtup_prepare_info (TYPE_4__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  slot_getallattrs (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static bool
printtup_20(TupleTableSlot *slot, DestReceiver *self)
{
	TupleDesc	typeinfo = slot->tts_tupleDescriptor;
	DR_printtup *myState = (DR_printtup *) self;
	MemoryContext oldcontext;
	StringInfo	buf = &myState->buf;
	int			natts = typeinfo->natts;
	int			i,
				j,
				k;

	/* Set or update my derived attribute info, if needed */
	if (myState->attrinfo != typeinfo || myState->nattrs != natts)
		printtup_prepare_info(myState, typeinfo, natts);

	/* Make sure the tuple is fully deconstructed */
	slot_getallattrs(slot);

	/* Switch into per-row context so we can recover memory below */
	oldcontext = MemoryContextSwitchTo(myState->tmpcontext);

	/*
	 * tell the frontend to expect new tuple data (in ASCII style)
	 */
	pq_beginmessage_reuse(buf, 'D');

	/*
	 * send a bitmap of which attributes are not null
	 */
	j = 0;
	k = 1 << 7;
	for (i = 0; i < natts; ++i)
	{
		if (!slot->tts_isnull[i])
			j |= k;				/* set bit if not null */
		k >>= 1;
		if (k == 0)				/* end of byte? */
		{
			pq_sendint8(buf, j);
			j = 0;
			k = 1 << 7;
		}
	}
	if (k != (1 << 7))			/* flush last partial byte */
		pq_sendint8(buf, j);

	/*
	 * send the attributes of this tuple
	 */
	for (i = 0; i < natts; ++i)
	{
		PrinttupAttrInfo *thisState = myState->myinfo + i;
		Datum		attr = slot->tts_values[i];
		char	   *outputstr;

		if (slot->tts_isnull[i])
			continue;

		Assert(thisState->format == 0);

		outputstr = OutputFunctionCall(&thisState->finfo, attr);
		pq_sendcountedtext(buf, outputstr, strlen(outputstr), true);
	}

	pq_endmessage_reuse(buf);

	/* Return to caller's context, and flush row's temporary memory */
	MemoryContextSwitchTo(oldcontext);
	MemoryContextReset(myState->tmpcontext);

	return true;
}