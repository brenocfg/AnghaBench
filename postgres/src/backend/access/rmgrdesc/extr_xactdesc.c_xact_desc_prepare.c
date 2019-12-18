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
struct TYPE_6__ {int /*<<< orphan*/  initfileinval; } ;
typedef  TYPE_1__ xl_xact_prepare ;
struct TYPE_7__ {int /*<<< orphan*/  tsId; int /*<<< orphan*/  dbId; int /*<<< orphan*/  msgs; int /*<<< orphan*/  nmsgs; int /*<<< orphan*/  subxacts; int /*<<< orphan*/  nsubxacts; int /*<<< orphan*/  abortnodes; int /*<<< orphan*/  nabortrels; int /*<<< orphan*/  xnodes; int /*<<< orphan*/  nrels; int /*<<< orphan*/  xact_time; int /*<<< orphan*/  twophase_gid; } ;
typedef  TYPE_2__ xl_xact_parsed_prepare ;
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ParsePrepareRecord (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standby_desc_invalidations (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timestamptz_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xact_desc_relations (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xact_desc_subxacts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xact_desc_prepare(StringInfo buf, uint8 info, xl_xact_prepare *xlrec)
{
	xl_xact_parsed_prepare parsed;

	ParsePrepareRecord(info, xlrec, &parsed);

	appendStringInfo(buf, "gid %s: ", parsed.twophase_gid);
	appendStringInfoString(buf, timestamptz_to_str(parsed.xact_time));

	xact_desc_relations(buf, "rels(commit)", parsed.nrels, parsed.xnodes);
	xact_desc_relations(buf, "rels(abort)", parsed.nabortrels,
						parsed.abortnodes);
	xact_desc_subxacts(buf, parsed.nsubxacts, parsed.subxacts);

	standby_desc_invalidations(
						buf, parsed.nmsgs, parsed.msgs, parsed.dbId, parsed.tsId,
						xlrec->initfileinval);
}