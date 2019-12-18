#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ relId; } ;
struct TYPE_9__ {scalar_t__ dbId; } ;
struct TYPE_8__ {scalar_t__ relId; } ;
struct TYPE_7__ {scalar_t__ catId; } ;
struct TYPE_11__ {scalar_t__ id; TYPE_4__ sn; TYPE_3__ rm; TYPE_2__ rc; TYPE_1__ cat; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_5__ SharedInvalidationMessage ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ SHAREDINVALCATALOG_ID ; 
 scalar_t__ SHAREDINVALRELCACHE_ID ; 
 scalar_t__ SHAREDINVALRELMAP_ID ; 
 scalar_t__ SHAREDINVALSMGR_ID ; 
 scalar_t__ SHAREDINVALSNAPSHOT_ID ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 

void
standby_desc_invalidations(StringInfo buf,
						   int nmsgs, SharedInvalidationMessage *msgs,
						   Oid dbId, Oid tsId,
						   bool relcacheInitFileInval)
{
	int			i;

	/* Do nothing if there are no invalidation messages */
	if (nmsgs <= 0)
		return;

	if (relcacheInitFileInval)
		appendStringInfo(buf, "; relcache init file inval dbid %u tsid %u",
						 dbId, tsId);

	appendStringInfoString(buf, "; inval msgs:");
	for (i = 0; i < nmsgs; i++)
	{
		SharedInvalidationMessage *msg = &msgs[i];

		if (msg->id >= 0)
			appendStringInfo(buf, " catcache %d", msg->id);
		else if (msg->id == SHAREDINVALCATALOG_ID)
			appendStringInfo(buf, " catalog %u", msg->cat.catId);
		else if (msg->id == SHAREDINVALRELCACHE_ID)
			appendStringInfo(buf, " relcache %u", msg->rc.relId);
		/* not expected, but print something anyway */
		else if (msg->id == SHAREDINVALSMGR_ID)
			appendStringInfoString(buf, " smgr");
		/* not expected, but print something anyway */
		else if (msg->id == SHAREDINVALRELMAP_ID)
			appendStringInfo(buf, " relmap db %u", msg->rm.dbId);
		else if (msg->id == SHAREDINVALSNAPSHOT_ID)
			appendStringInfo(buf, " snapshot %u", msg->sn.relId);
		else
			appendStringInfo(buf, " unrecognized id %d", msg->id);
	}
}