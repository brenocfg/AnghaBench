#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_10__ {int /*<<< orphan*/  atttypid; } ;
struct TYPE_9__ {int natts; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* TupleDescAttr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  printatt (unsigned int,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  slot_getattr (TYPE_1__*,int,int*) ; 

bool
debugtup(TupleTableSlot *slot, DestReceiver *self)
{
	TupleDesc	typeinfo = slot->tts_tupleDescriptor;
	int			natts = typeinfo->natts;
	int			i;
	Datum		attr;
	char	   *value;
	bool		isnull;
	Oid			typoutput;
	bool		typisvarlena;

	for (i = 0; i < natts; ++i)
	{
		attr = slot_getattr(slot, i + 1, &isnull);
		if (isnull)
			continue;
		getTypeOutputInfo(TupleDescAttr(typeinfo, i)->atttypid,
						  &typoutput, &typisvarlena);

		value = OidOutputFunctionCall(typoutput, attr);

		printatt((unsigned) i + 1, TupleDescAttr(typeinfo, i), value);
	}
	printf("\t----\n");

	return true;
}