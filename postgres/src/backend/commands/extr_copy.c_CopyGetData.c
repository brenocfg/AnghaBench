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
struct TYPE_7__ {int cursor; int len; } ;
struct TYPE_6__ {int copy_dest; int reached_eof; int (* data_source_cb ) (void*,int,int) ;TYPE_2__* fe_msgbuf; int /*<<< orphan*/  copy_file; } ;
typedef  TYPE_1__* CopyState ;

/* Variables and functions */
#define  COPY_CALLBACK 131 
#define  COPY_FILE 130 
#define  COPY_NEW_FE 129 
#define  COPY_OLD_FE 128 
 int EOF ; 
 int /*<<< orphan*/  ERRCODE_CONNECTION_FAILURE ; 
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  ERRCODE_QUERY_CANCELED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HOLD_CANCEL_INTERRUPTS () ; 
 int /*<<< orphan*/  RESUME_CANCEL_INTERRUPTS () ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ ) ; 
 int fread (void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_copymsgbytes (TYPE_2__*,void*,int) ; 
 int pq_getbyte () ; 
 int /*<<< orphan*/  pq_getbytes (char*,int) ; 
 int /*<<< orphan*/  pq_getmessage (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int pq_getmsgstring (TYPE_2__*) ; 
 int /*<<< orphan*/  pq_startmsgread () ; 
 int stub1 (void*,int,int) ; 

__attribute__((used)) static int
CopyGetData(CopyState cstate, void *databuf, int minread, int maxread)
{
	int			bytesread = 0;

	switch (cstate->copy_dest)
	{
		case COPY_FILE:
			bytesread = fread(databuf, 1, maxread, cstate->copy_file);
			if (ferror(cstate->copy_file))
				ereport(ERROR,
						(errcode_for_file_access(),
						 errmsg("could not read from COPY file: %m")));
			if (bytesread == 0)
				cstate->reached_eof = true;
			break;
		case COPY_OLD_FE:

			/*
			 * We cannot read more than minread bytes (which in practice is 1)
			 * because old protocol doesn't have any clear way of separating
			 * the COPY stream from following data.  This is slow, but not any
			 * slower than the code path was originally, and we don't care
			 * much anymore about the performance of old protocol.
			 */
			if (pq_getbytes((char *) databuf, minread))
			{
				/* Only a \. terminator is legal EOF in old protocol */
				ereport(ERROR,
						(errcode(ERRCODE_CONNECTION_FAILURE),
						 errmsg("unexpected EOF on client connection with an open transaction")));
			}
			bytesread = minread;
			break;
		case COPY_NEW_FE:
			while (maxread > 0 && bytesread < minread && !cstate->reached_eof)
			{
				int			avail;

				while (cstate->fe_msgbuf->cursor >= cstate->fe_msgbuf->len)
				{
					/* Try to receive another message */
					int			mtype;

			readmessage:
					HOLD_CANCEL_INTERRUPTS();
					pq_startmsgread();
					mtype = pq_getbyte();
					if (mtype == EOF)
						ereport(ERROR,
								(errcode(ERRCODE_CONNECTION_FAILURE),
								 errmsg("unexpected EOF on client connection with an open transaction")));
					if (pq_getmessage(cstate->fe_msgbuf, 0))
						ereport(ERROR,
								(errcode(ERRCODE_CONNECTION_FAILURE),
								 errmsg("unexpected EOF on client connection with an open transaction")));
					RESUME_CANCEL_INTERRUPTS();
					switch (mtype)
					{
						case 'd':	/* CopyData */
							break;
						case 'c':	/* CopyDone */
							/* COPY IN correctly terminated by frontend */
							cstate->reached_eof = true;
							return bytesread;
						case 'f':	/* CopyFail */
							ereport(ERROR,
									(errcode(ERRCODE_QUERY_CANCELED),
									 errmsg("COPY from stdin failed: %s",
											pq_getmsgstring(cstate->fe_msgbuf))));
							break;
						case 'H':	/* Flush */
						case 'S':	/* Sync */

							/*
							 * Ignore Flush/Sync for the convenience of client
							 * libraries (such as libpq) that may send those
							 * without noticing that the command they just
							 * sent was COPY.
							 */
							goto readmessage;
						default:
							ereport(ERROR,
									(errcode(ERRCODE_PROTOCOL_VIOLATION),
									 errmsg("unexpected message type 0x%02X during COPY from stdin",
											mtype)));
							break;
					}
				}
				avail = cstate->fe_msgbuf->len - cstate->fe_msgbuf->cursor;
				if (avail > maxread)
					avail = maxread;
				pq_copymsgbytes(cstate->fe_msgbuf, databuf, avail);
				databuf = (void *) ((char *) databuf + avail);
				maxread -= avail;
				bytesread += avail;
			}
			break;
		case COPY_CALLBACK:
			bytesread = cstate->data_source_cb(databuf, minread, maxread);
			break;
	}

	return bytesread;
}