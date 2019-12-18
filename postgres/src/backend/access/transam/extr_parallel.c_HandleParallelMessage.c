#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_18__ {int /*<<< orphan*/  context; int /*<<< orphan*/  elevel; } ;
struct TYPE_17__ {int* known_attached_workers; TYPE_1__* worker; int /*<<< orphan*/ * error_context_stack; int /*<<< orphan*/  nknown_attached_workers; } ;
struct TYPE_16__ {int /*<<< orphan*/  len; } ;
struct TYPE_15__ {int /*<<< orphan*/ * error_mqh; int /*<<< orphan*/  pid; } ;
typedef  TYPE_2__* StringInfo ;
typedef  TYPE_3__ ParallelContext ;
typedef  TYPE_4__ ErrorData ;
typedef  int /*<<< orphan*/  ErrorContextCallback ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FORCE_PARALLEL_REGRESS ; 
 int /*<<< orphan*/  Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NotifyMyFrontEnd (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ThrowErrorData (TYPE_4__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * error_context_stack ; 
 int /*<<< orphan*/  force_parallel_mode ; 
 int /*<<< orphan*/  pq_endmessage (TYPE_2__*) ; 
 char pq_getmsgbyte (TYPE_2__*) ; 
 int /*<<< orphan*/  pq_getmsgend (TYPE_2__*) ; 
 int /*<<< orphan*/  pq_getmsgint (TYPE_2__*,int) ; 
 char* pq_getmsgrawstring (TYPE_2__*) ; 
 int /*<<< orphan*/  pq_parse_errornotice (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  psprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_mq_detach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
HandleParallelMessage(ParallelContext *pcxt, int i, StringInfo msg)
{
	char		msgtype;

	if (pcxt->known_attached_workers != NULL &&
		!pcxt->known_attached_workers[i])
	{
		pcxt->known_attached_workers[i] = true;
		pcxt->nknown_attached_workers++;
	}

	msgtype = pq_getmsgbyte(msg);

	switch (msgtype)
	{
		case 'K':				/* BackendKeyData */
			{
				int32		pid = pq_getmsgint(msg, 4);

				(void) pq_getmsgint(msg, 4);	/* discard cancel key */
				(void) pq_getmsgend(msg);
				pcxt->worker[i].pid = pid;
				break;
			}

		case 'E':				/* ErrorResponse */
		case 'N':				/* NoticeResponse */
			{
				ErrorData	edata;
				ErrorContextCallback *save_error_context_stack;

				/* Parse ErrorResponse or NoticeResponse. */
				pq_parse_errornotice(msg, &edata);

				/* Death of a worker isn't enough justification for suicide. */
				edata.elevel = Min(edata.elevel, ERROR);

				/*
				 * If desired, add a context line to show that this is a
				 * message propagated from a parallel worker.  Otherwise, it
				 * can sometimes be confusing to understand what actually
				 * happened.  (We don't do this in FORCE_PARALLEL_REGRESS mode
				 * because it causes test-result instability depending on
				 * whether a parallel worker is actually used or not.)
				 */
				if (force_parallel_mode != FORCE_PARALLEL_REGRESS)
				{
					if (edata.context)
						edata.context = psprintf("%s\n%s", edata.context,
												 _("parallel worker"));
					else
						edata.context = pstrdup(_("parallel worker"));
				}

				/*
				 * Context beyond that should use the error context callbacks
				 * that were in effect when the ParallelContext was created,
				 * not the current ones.
				 */
				save_error_context_stack = error_context_stack;
				error_context_stack = pcxt->error_context_stack;

				/* Rethrow error or print notice. */
				ThrowErrorData(&edata);

				/* Not an error, so restore previous context stack. */
				error_context_stack = save_error_context_stack;

				break;
			}

		case 'A':				/* NotifyResponse */
			{
				/* Propagate NotifyResponse. */
				int32		pid;
				const char *channel;
				const char *payload;

				pid = pq_getmsgint(msg, 4);
				channel = pq_getmsgrawstring(msg);
				payload = pq_getmsgrawstring(msg);
				pq_endmessage(msg);

				NotifyMyFrontEnd(channel, payload, pid);

				break;
			}

		case 'X':				/* Terminate, indicating clean exit */
			{
				shm_mq_detach(pcxt->worker[i].error_mqh);
				pcxt->worker[i].error_mqh = NULL;
				break;
			}

		default:
			{
				elog(ERROR, "unrecognized message type received from parallel worker: %c (message length %d bytes)",
					 msgtype, msg->len);
			}
	}
}