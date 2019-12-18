#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sync; } ;
struct TYPE_6__ {TYPE_1__ syncpt; } ;
struct lrd {TYPE_2__ log; scalar_t__ length; void* type; scalar_t__ backchain; scalar_t__ logtid; } ;
struct logsuper {void* end; void* state; } ;
struct TYPE_8__ {void* eor; } ;
struct TYPE_7__ {void* eor; } ;
struct logpage {TYPE_4__ t; TYPE_3__ h; } ;
struct lbuf {scalar_t__ l_ldata; int /*<<< orphan*/  l_eor; } ;
struct jfs_log {int /*<<< orphan*/  eor; int /*<<< orphan*/  page; struct lbuf* bp; } ;

/* Variables and functions */
 int LOGREDONE ; 
 int /*<<< orphan*/  LOG_SYNCPT ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  jfs_flush_journal (struct jfs_log*,int) ; 
 int /*<<< orphan*/  jfs_info (char*,...) ; 
 int /*<<< orphan*/  jfs_warn (char*,int) ; 
 int /*<<< orphan*/  lbmDirectWrite (struct jfs_log*,struct lbuf*,int) ; 
 int /*<<< orphan*/  lbmFREE ; 
 int lbmIOWait (struct lbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbmLogShutdown (struct jfs_log*) ; 
 int lbmRELEASE ; 
 int lbmRead (struct jfs_log*,int,struct lbuf**) ; 
 int lbmSYNC ; 
 int lbmWRITE ; 
 int /*<<< orphan*/  lbmWrite (struct jfs_log*,struct lbuf*,int,int /*<<< orphan*/ ) ; 
 int lmWriteRecord (struct jfs_log*,int /*<<< orphan*/ *,struct lrd*,int /*<<< orphan*/ *) ; 

int lmLogShutdown(struct jfs_log * log)
{
	int rc;
	struct lrd lrd;
	int lsn;
	struct logsuper *logsuper;
	struct lbuf *bpsuper;
	struct lbuf *bp;
	struct logpage *lp;

	jfs_info("lmLogShutdown: log:0x%p", log);

	jfs_flush_journal(log, 2);

	/*
	 * write the last SYNCPT record with syncpoint = 0
	 * (i.e., log redo up to HERE !)
	 */
	lrd.logtid = 0;
	lrd.backchain = 0;
	lrd.type = cpu_to_le16(LOG_SYNCPT);
	lrd.length = 0;
	lrd.log.syncpt.sync = 0;

	lsn = lmWriteRecord(log, NULL, &lrd, NULL);
	bp = log->bp;
	lp = (struct logpage *) bp->l_ldata;
	lp->h.eor = lp->t.eor = cpu_to_le16(bp->l_eor);
	lbmWrite(log, log->bp, lbmWRITE | lbmRELEASE | lbmSYNC, 0);
	lbmIOWait(log->bp, lbmFREE);
	log->bp = NULL;

	/*
	 * synchronous update log superblock
	 * mark log state as shutdown cleanly
	 * (i.e., Log does not need to be replayed).
	 */
	if ((rc = lbmRead(log, 1, &bpsuper)))
		goto out;

	logsuper = (struct logsuper *) bpsuper->l_ldata;
	logsuper->state = cpu_to_le32(LOGREDONE);
	logsuper->end = cpu_to_le32(lsn);
	lbmDirectWrite(log, bpsuper, lbmWRITE | lbmRELEASE | lbmSYNC);
	rc = lbmIOWait(bpsuper, lbmFREE);

	jfs_info("lmLogShutdown: lsn:0x%x page:%d eor:%d",
		 lsn, log->page, log->eor);

      out:
	/*
	 * shutdown per log i/o
	 */
	lbmLogShutdown(log);

	if (rc) {
		jfs_warn("lmLogShutdown: exit(%d)", rc);
	}
	return rc;
}