#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct RELCACHECALLBACK {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* function ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_16__ {int backend; int /*<<< orphan*/  node; } ;
struct TYPE_14__ {scalar_t__ dbId; } ;
struct TYPE_13__ {int backend_hi; scalar_t__ backend_lo; int /*<<< orphan*/  rnode; } ;
struct TYPE_12__ {scalar_t__ dbId; scalar_t__ relId; } ;
struct TYPE_11__ {scalar_t__ dbId; int /*<<< orphan*/  catId; } ;
struct TYPE_10__ {scalar_t__ dbId; int /*<<< orphan*/  hashValue; int /*<<< orphan*/  id; } ;
struct TYPE_15__ {scalar_t__ id; TYPE_5__ rm; TYPE_4__ sm; TYPE_3__ rc; TYPE_2__ cat; TYPE_1__ cc; } ;
typedef  TYPE_6__ SharedInvalidationMessage ;
typedef  TYPE_7__ RelFileNodeBackend ;

/* Variables and functions */
 int /*<<< orphan*/  CallSyscacheCallbacks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogCacheFlushCatalog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FATAL ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvalidateCatalogSnapshot () ; 
 scalar_t__ MyDatabaseId ; 
 int /*<<< orphan*/  RelationCacheInvalidate () ; 
 int /*<<< orphan*/  RelationCacheInvalidateEntry (scalar_t__) ; 
 int /*<<< orphan*/  RelationMapInvalidate (int) ; 
 scalar_t__ SHAREDINVALCATALOG_ID ; 
 scalar_t__ SHAREDINVALRELCACHE_ID ; 
 scalar_t__ SHAREDINVALRELMAP_ID ; 
 scalar_t__ SHAREDINVALSMGR_ID ; 
 scalar_t__ SHAREDINVALSNAPSHOT_ID ; 
 int /*<<< orphan*/  SysCacheInvalidate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int relcache_callback_count ; 
 struct RELCACHECALLBACK* relcache_callback_list ; 
 int /*<<< orphan*/  smgrclosenode (TYPE_7__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

void
LocalExecuteInvalidationMessage(SharedInvalidationMessage *msg)
{
	if (msg->id >= 0)
	{
		if (msg->cc.dbId == MyDatabaseId || msg->cc.dbId == InvalidOid)
		{
			InvalidateCatalogSnapshot();

			SysCacheInvalidate(msg->cc.id, msg->cc.hashValue);

			CallSyscacheCallbacks(msg->cc.id, msg->cc.hashValue);
		}
	}
	else if (msg->id == SHAREDINVALCATALOG_ID)
	{
		if (msg->cat.dbId == MyDatabaseId || msg->cat.dbId == InvalidOid)
		{
			InvalidateCatalogSnapshot();

			CatalogCacheFlushCatalog(msg->cat.catId);

			/* CatalogCacheFlushCatalog calls CallSyscacheCallbacks as needed */
		}
	}
	else if (msg->id == SHAREDINVALRELCACHE_ID)
	{
		if (msg->rc.dbId == MyDatabaseId || msg->rc.dbId == InvalidOid)
		{
			int			i;

			if (msg->rc.relId == InvalidOid)
				RelationCacheInvalidate();
			else
				RelationCacheInvalidateEntry(msg->rc.relId);

			for (i = 0; i < relcache_callback_count; i++)
			{
				struct RELCACHECALLBACK *ccitem = relcache_callback_list + i;

				ccitem->function(ccitem->arg, msg->rc.relId);
			}
		}
	}
	else if (msg->id == SHAREDINVALSMGR_ID)
	{
		/*
		 * We could have smgr entries for relations of other databases, so no
		 * short-circuit test is possible here.
		 */
		RelFileNodeBackend rnode;

		rnode.node = msg->sm.rnode;
		rnode.backend = (msg->sm.backend_hi << 16) | (int) msg->sm.backend_lo;
		smgrclosenode(rnode);
	}
	else if (msg->id == SHAREDINVALRELMAP_ID)
	{
		/* We only care about our own database and shared catalogs */
		if (msg->rm.dbId == InvalidOid)
			RelationMapInvalidate(true);
		else if (msg->rm.dbId == MyDatabaseId)
			RelationMapInvalidate(false);
	}
	else if (msg->id == SHAREDINVALSNAPSHOT_ID)
	{
		/* We only care about our own database and shared catalogs */
		if (msg->rm.dbId == InvalidOid)
			InvalidateCatalogSnapshot();
		else if (msg->rm.dbId == MyDatabaseId)
			InvalidateCatalogSnapshot();
	}
	else
		elog(FATAL, "unrecognized SI message ID: %d", msg->id);
}