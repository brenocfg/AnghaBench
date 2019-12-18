#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_7__ {int attlen; int atttypmod; scalar_t__ atttypid; int /*<<< orphan*/  attname; } ;
struct TYPE_6__ {int natts; } ;
typedef  int /*<<< orphan*/  StringInfoData ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  DestReceiver ;

/* Variables and functions */
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pq_beginmessage (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendint16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
printsimple_startup(DestReceiver *self, int operation, TupleDesc tupdesc)
{
	StringInfoData buf;
	int			i;

	pq_beginmessage(&buf, 'T'); /* RowDescription */
	pq_sendint16(&buf, tupdesc->natts);

	for (i = 0; i < tupdesc->natts; ++i)
	{
		Form_pg_attribute attr = TupleDescAttr(tupdesc, i);

		pq_sendstring(&buf, NameStr(attr->attname));
		pq_sendint32(&buf, 0);	/* table oid */
		pq_sendint16(&buf, 0);	/* attnum */
		pq_sendint32(&buf, (int) attr->atttypid);
		pq_sendint16(&buf, attr->attlen);
		pq_sendint32(&buf, attr->atttypmod);
		pq_sendint16(&buf, 0);	/* format code */
	}

	pq_endmessage(&buf);
}