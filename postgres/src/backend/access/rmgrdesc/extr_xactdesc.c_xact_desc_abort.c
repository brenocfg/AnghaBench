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
struct TYPE_6__ {int /*<<< orphan*/  subxacts; int /*<<< orphan*/  nsubxacts; int /*<<< orphan*/  xnodes; int /*<<< orphan*/  nrels; int /*<<< orphan*/  twophase_xid; } ;
typedef  TYPE_1__ xl_xact_parsed_abort ;
struct TYPE_7__ {int /*<<< orphan*/  xact_time; } ;
typedef  TYPE_2__ xl_xact_abort ;
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ParseAbortRecord (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ TransactionIdIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timestamptz_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xact_desc_relations (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xact_desc_subxacts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xact_desc_abort(StringInfo buf, uint8 info, xl_xact_abort *xlrec)
{
	xl_xact_parsed_abort parsed;

	ParseAbortRecord(info, xlrec, &parsed);

	/* If this is a prepared xact, show the xid of the original xact */
	if (TransactionIdIsValid(parsed.twophase_xid))
		appendStringInfo(buf, "%u: ", parsed.twophase_xid);

	appendStringInfoString(buf, timestamptz_to_str(xlrec->xact_time));

	xact_desc_relations(buf, "rels", parsed.nrels, parsed.xnodes);
	xact_desc_subxacts(buf, parsed.nsubxacts, parsed.subxacts);
}