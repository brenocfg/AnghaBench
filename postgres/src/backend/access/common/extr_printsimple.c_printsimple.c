#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_8__ {int /*<<< orphan*/ * tts_values; scalar_t__* tts_isnull; TYPE_2__* tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
typedef  TYPE_2__* TupleDesc ;
struct TYPE_10__ {int atttypid; } ;
struct TYPE_9__ {int natts; } ;
typedef  int /*<<< orphan*/  StringInfoData ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  DestReceiver ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetTextPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
#define  INT4OID 130 
#define  INT8OID 129 
#define  TEXTOID 128 
 TYPE_3__* TupleDescAttr (TYPE_2__*,int) ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pg_lltoa (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pg_ltoa (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pq_beginmessage (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pq_endmessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendcountedtext (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pq_sendint16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  slot_getallattrs (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

bool
printsimple(TupleTableSlot *slot, DestReceiver *self)
{
	TupleDesc	tupdesc = slot->tts_tupleDescriptor;
	StringInfoData buf;
	int			i;

	/* Make sure the tuple is fully deconstructed */
	slot_getallattrs(slot);

	/* Prepare and send message */
	pq_beginmessage(&buf, 'D');
	pq_sendint16(&buf, tupdesc->natts);

	for (i = 0; i < tupdesc->natts; ++i)
	{
		Form_pg_attribute attr = TupleDescAttr(tupdesc, i);
		Datum		value;

		if (slot->tts_isnull[i])
		{
			pq_sendint32(&buf, -1);
			continue;
		}

		value = slot->tts_values[i];

		/*
		 * We can't call the regular type output functions here because we
		 * might not have catalog access.  Instead, we must hard-wire
		 * knowledge of the required types.
		 */
		switch (attr->atttypid)
		{
			case TEXTOID:
				{
					text	   *t = DatumGetTextPP(value);

					pq_sendcountedtext(&buf,
									   VARDATA_ANY(t),
									   VARSIZE_ANY_EXHDR(t),
									   false);
				}
				break;

			case INT4OID:
				{
					int32		num = DatumGetInt32(value);
					char		str[12];	/* sign, 10 digits and '\0' */

					pg_ltoa(num, str);
					pq_sendcountedtext(&buf, str, strlen(str), false);
				}
				break;

			case INT8OID:
				{
					int64		num = DatumGetInt64(value);
					char		str[23];	/* sign, 21 digits and '\0' */

					pg_lltoa(num, str);
					pq_sendcountedtext(&buf, str, strlen(str), false);
				}
				break;

			default:
				elog(ERROR, "unsupported type OID: %u", attr->atttypid);
		}
	}

	pq_endmessage(&buf);

	return true;
}