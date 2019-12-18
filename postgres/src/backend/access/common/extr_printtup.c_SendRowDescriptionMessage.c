#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_5__ {int natts; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  FrontendProtocol ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendRowDescriptionCols_2 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendRowDescriptionCols_3 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_beginmessage_reuse (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pq_endmessage_reuse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendint16 (int /*<<< orphan*/ ,int) ; 

void
SendRowDescriptionMessage(StringInfo buf, TupleDesc typeinfo,
						  List *targetlist, int16 *formats)
{
	int			natts = typeinfo->natts;
	int			proto = PG_PROTOCOL_MAJOR(FrontendProtocol);

	/* tuple descriptor message type */
	pq_beginmessage_reuse(buf, 'T');
	/* # of attrs in tuples */
	pq_sendint16(buf, natts);

	if (proto >= 3)
		SendRowDescriptionCols_3(buf, typeinfo, targetlist, formats);
	else
		SendRowDescriptionCols_2(buf, typeinfo, targetlist, formats);

	pq_endmessage_reuse(buf);
}