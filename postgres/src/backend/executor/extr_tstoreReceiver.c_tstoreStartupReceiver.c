#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* TupleDesc ;
struct TYPE_11__ {int attlen; scalar_t__ attisdropped; } ;
struct TYPE_8__ {int /*<<< orphan*/  receiveSlot; } ;
struct TYPE_10__ {int /*<<< orphan*/ * tofree; int /*<<< orphan*/ * outvalues; TYPE_1__ pub; int /*<<< orphan*/  cxt; scalar_t__ detoast; } ;
struct TYPE_9__ {int natts; } ;
typedef  TYPE_3__ TStoreState ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* TupleDescAttr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tstoreReceiveSlot_detoast ; 
 int /*<<< orphan*/  tstoreReceiveSlot_notoast ; 

__attribute__((used)) static void
tstoreStartupReceiver(DestReceiver *self, int operation, TupleDesc typeinfo)
{
	TStoreState *myState = (TStoreState *) self;
	bool		needtoast = false;
	int			natts = typeinfo->natts;
	int			i;

	/* Check if any columns require detoast work */
	if (myState->detoast)
	{
		for (i = 0; i < natts; i++)
		{
			Form_pg_attribute attr = TupleDescAttr(typeinfo, i);

			if (attr->attisdropped)
				continue;
			if (attr->attlen == -1)
			{
				needtoast = true;
				break;
			}
		}
	}

	/* Set up appropriate callback */
	if (needtoast)
	{
		myState->pub.receiveSlot = tstoreReceiveSlot_detoast;
		/* Create workspace */
		myState->outvalues = (Datum *)
			MemoryContextAlloc(myState->cxt, natts * sizeof(Datum));
		myState->tofree = (Datum *)
			MemoryContextAlloc(myState->cxt, natts * sizeof(Datum));
	}
	else
	{
		myState->pub.receiveSlot = tstoreReceiveSlot_notoast;
		myState->outvalues = NULL;
		myState->tofree = NULL;
	}
}