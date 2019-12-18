#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ xl_seq_rec ;
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ XLogRecPtr ;
struct TYPE_21__ {scalar_t__ seqincrement; scalar_t__ seqmax; scalar_t__ seqmin; scalar_t__ seqcache; int seqcycle; } ;
struct TYPE_20__ {scalar_t__ last_value; scalar_t__ log_cnt; int is_called; } ;
struct TYPE_19__ {int t_len; scalar_t__ t_data; } ;
struct TYPE_18__ {int /*<<< orphan*/  rd_node; int /*<<< orphan*/  rd_islocaltemp; } ;
struct TYPE_17__ {scalar_t__ last; scalar_t__ cached; int last_valid; scalar_t__ increment; int /*<<< orphan*/  relid; } ;
typedef  TYPE_2__* SeqTable ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  Page ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ HeapTupleData ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_5__* Form_pg_sequence_data ;
typedef  TYPE_6__* Form_pg_sequence ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ ACLCHECK_OK ; 
 int ACL_UPDATE ; 
 int ACL_USAGE ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BufferGetPage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  END_CRIT_SECTION () ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERRCODE_SEQUENCE_GENERATOR_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ GetRedoRecPtr () ; 
 int /*<<< orphan*/  GetTopTransactionId () ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 char* INT64_FORMAT ; 
 int /*<<< orphan*/  MarkBufferDirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ PageGetLSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PageSetLSN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PreventCommandIfParallelMode (char*) ; 
 int /*<<< orphan*/  PreventCommandIfReadOnly (char*) ; 
 int /*<<< orphan*/  REGBUF_WILL_INIT ; 
 int /*<<< orphan*/  RM_SEQ_ID ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 scalar_t__ RelationNeedsWAL (TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQRELID ; 
 scalar_t__ SEQ_LOG_VALS ; 
 int /*<<< orphan*/  START_CRIT_SECTION () ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockReleaseBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLOG_SEQ_LOG ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 scalar_t__ XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  init_sequence (int /*<<< orphan*/ ,TYPE_2__**,TYPE_3__**) ; 
 TYPE_2__* last_used_seq ; 
 scalar_t__ pg_class_aclcheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* read_seq_tuple (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  relation_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 

int64
nextval_internal(Oid relid, bool check_permissions)
{
	SeqTable	elm;
	Relation	seqrel;
	Buffer		buf;
	Page		page;
	HeapTuple	pgstuple;
	Form_pg_sequence pgsform;
	HeapTupleData seqdatatuple;
	Form_pg_sequence_data seq;
	int64		incby,
				maxv,
				minv,
				cache,
				log,
				fetch,
				last;
	int64		result,
				next,
				rescnt = 0;
	bool		cycle;
	bool		logit = false;

	/* open and lock sequence */
	init_sequence(relid, &elm, &seqrel);

	if (check_permissions &&
		pg_class_aclcheck(elm->relid, GetUserId(),
						  ACL_USAGE | ACL_UPDATE) != ACLCHECK_OK)
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
				 errmsg("permission denied for sequence %s",
						RelationGetRelationName(seqrel))));

	/* read-only transactions may only modify temp sequences */
	if (!seqrel->rd_islocaltemp)
		PreventCommandIfReadOnly("nextval()");

	/*
	 * Forbid this during parallel operation because, to make it work, the
	 * cooperating backends would need to share the backend-local cached
	 * sequence information.  Currently, we don't support that.
	 */
	PreventCommandIfParallelMode("nextval()");

	if (elm->last != elm->cached)	/* some numbers were cached */
	{
		Assert(elm->last_valid);
		Assert(elm->increment != 0);
		elm->last += elm->increment;
		relation_close(seqrel, NoLock);
		last_used_seq = elm;
		return elm->last;
	}

	pgstuple = SearchSysCache1(SEQRELID, ObjectIdGetDatum(relid));
	if (!HeapTupleIsValid(pgstuple))
		elog(ERROR, "cache lookup failed for sequence %u", relid);
	pgsform = (Form_pg_sequence) GETSTRUCT(pgstuple);
	incby = pgsform->seqincrement;
	maxv = pgsform->seqmax;
	minv = pgsform->seqmin;
	cache = pgsform->seqcache;
	cycle = pgsform->seqcycle;
	ReleaseSysCache(pgstuple);

	/* lock page' buffer and read tuple */
	seq = read_seq_tuple(seqrel, &buf, &seqdatatuple);
	page = BufferGetPage(buf);

	elm->increment = incby;
	last = next = result = seq->last_value;
	fetch = cache;
	log = seq->log_cnt;

	if (!seq->is_called)
	{
		rescnt++;				/* return last_value if not is_called */
		fetch--;
	}

	/*
	 * Decide whether we should emit a WAL log record.  If so, force up the
	 * fetch count to grab SEQ_LOG_VALS more values than we actually need to
	 * cache.  (These will then be usable without logging.)
	 *
	 * If this is the first nextval after a checkpoint, we must force a new
	 * WAL record to be written anyway, else replay starting from the
	 * checkpoint would fail to advance the sequence past the logged values.
	 * In this case we may as well fetch extra values.
	 */
	if (log < fetch || !seq->is_called)
	{
		/* forced log to satisfy local demand for values */
		fetch = log = fetch + SEQ_LOG_VALS;
		logit = true;
	}
	else
	{
		XLogRecPtr	redoptr = GetRedoRecPtr();

		if (PageGetLSN(page) <= redoptr)
		{
			/* last update of seq was before checkpoint */
			fetch = log = fetch + SEQ_LOG_VALS;
			logit = true;
		}
	}

	while (fetch)				/* try to fetch cache [+ log ] numbers */
	{
		/*
		 * Check MAXVALUE for ascending sequences and MINVALUE for descending
		 * sequences
		 */
		if (incby > 0)
		{
			/* ascending sequence */
			if ((maxv >= 0 && next > maxv - incby) ||
				(maxv < 0 && next + incby > maxv))
			{
				if (rescnt > 0)
					break;		/* stop fetching */
				if (!cycle)
				{
					char		buf[100];

					snprintf(buf, sizeof(buf), INT64_FORMAT, maxv);
					ereport(ERROR,
							(errcode(ERRCODE_SEQUENCE_GENERATOR_LIMIT_EXCEEDED),
							 errmsg("nextval: reached maximum value of sequence \"%s\" (%s)",
									RelationGetRelationName(seqrel), buf)));
				}
				next = minv;
			}
			else
				next += incby;
		}
		else
		{
			/* descending sequence */
			if ((minv < 0 && next < minv - incby) ||
				(minv >= 0 && next + incby < minv))
			{
				if (rescnt > 0)
					break;		/* stop fetching */
				if (!cycle)
				{
					char		buf[100];

					snprintf(buf, sizeof(buf), INT64_FORMAT, minv);
					ereport(ERROR,
							(errcode(ERRCODE_SEQUENCE_GENERATOR_LIMIT_EXCEEDED),
							 errmsg("nextval: reached minimum value of sequence \"%s\" (%s)",
									RelationGetRelationName(seqrel), buf)));
				}
				next = maxv;
			}
			else
				next += incby;
		}
		fetch--;
		if (rescnt < cache)
		{
			log--;
			rescnt++;
			last = next;
			if (rescnt == 1)	/* if it's first result - */
				result = next;	/* it's what to return */
		}
	}

	log -= fetch;				/* adjust for any unfetched numbers */
	Assert(log >= 0);

	/* save info in local cache */
	elm->last = result;			/* last returned number */
	elm->cached = last;			/* last fetched number */
	elm->last_valid = true;

	last_used_seq = elm;

	/*
	 * If something needs to be WAL logged, acquire an xid, so this
	 * transaction's commit will trigger a WAL flush and wait for syncrep.
	 * It's sufficient to ensure the toplevel transaction has an xid, no need
	 * to assign xids subxacts, that'll already trigger an appropriate wait.
	 * (Have to do that here, so we're outside the critical section)
	 */
	if (logit && RelationNeedsWAL(seqrel))
		GetTopTransactionId();

	/* ready to change the on-disk (or really, in-buffer) tuple */
	START_CRIT_SECTION();

	/*
	 * We must mark the buffer dirty before doing XLogInsert(); see notes in
	 * SyncOneBuffer().  However, we don't apply the desired changes just yet.
	 * This looks like a violation of the buffer update protocol, but it is in
	 * fact safe because we hold exclusive lock on the buffer.  Any other
	 * process, including a checkpoint, that tries to examine the buffer
	 * contents will block until we release the lock, and then will see the
	 * final state that we install below.
	 */
	MarkBufferDirty(buf);

	/* XLOG stuff */
	if (logit && RelationNeedsWAL(seqrel))
	{
		xl_seq_rec	xlrec;
		XLogRecPtr	recptr;

		/*
		 * We don't log the current state of the tuple, but rather the state
		 * as it would appear after "log" more fetches.  This lets us skip
		 * that many future WAL records, at the cost that we lose those
		 * sequence values if we crash.
		 */
		XLogBeginInsert();
		XLogRegisterBuffer(0, buf, REGBUF_WILL_INIT);

		/* set values that will be saved in xlog */
		seq->last_value = next;
		seq->is_called = true;
		seq->log_cnt = 0;

		xlrec.node = seqrel->rd_node;

		XLogRegisterData((char *) &xlrec, sizeof(xl_seq_rec));
		XLogRegisterData((char *) seqdatatuple.t_data, seqdatatuple.t_len);

		recptr = XLogInsert(RM_SEQ_ID, XLOG_SEQ_LOG);

		PageSetLSN(page, recptr);
	}

	/* Now update sequence tuple to the intended final state */
	seq->last_value = last;		/* last fetched number */
	seq->is_called = true;
	seq->log_cnt = log;			/* how much is logged */

	END_CRIT_SECTION();

	UnlockReleaseBuffer(buf);

	relation_close(seqrel, NoLock);

	return result;
}