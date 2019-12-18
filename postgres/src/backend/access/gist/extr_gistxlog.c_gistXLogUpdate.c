#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ntodelete; int ntoinsert; } ;
typedef  TYPE_1__ gistxlogPageUpdate ;
typedef  int /*<<< orphan*/  XLogRecPtr ;
typedef  int /*<<< orphan*/  OffsetNumber ;
typedef  scalar_t__ IndexTuple ;
typedef  int /*<<< orphan*/  Buffer ;

/* Variables and functions */
 scalar_t__ BufferIsValid (int /*<<< orphan*/ ) ; 
 int IndexTupleSize (scalar_t__) ; 
 int /*<<< orphan*/  REGBUF_STANDARD ; 
 int /*<<< orphan*/  RM_GIST_ID ; 
 int /*<<< orphan*/  XLOG_GIST_PAGE_UPDATE ; 
 int /*<<< orphan*/  XLogBeginInsert () ; 
 int /*<<< orphan*/  XLogInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterBufData (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  XLogRegisterBuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLogRegisterData (char*,int) ; 

XLogRecPtr
gistXLogUpdate(Buffer buffer,
			   OffsetNumber *todelete, int ntodelete,
			   IndexTuple *itup, int ituplen,
			   Buffer leftchildbuf)
{
	gistxlogPageUpdate xlrec;
	int			i;
	XLogRecPtr	recptr;

	xlrec.ntodelete = ntodelete;
	xlrec.ntoinsert = ituplen;

	XLogBeginInsert();
	XLogRegisterData((char *) &xlrec, sizeof(gistxlogPageUpdate));

	XLogRegisterBuffer(0, buffer, REGBUF_STANDARD);
	XLogRegisterBufData(0, (char *) todelete, sizeof(OffsetNumber) * ntodelete);

	/* new tuples */
	for (i = 0; i < ituplen; i++)
		XLogRegisterBufData(0, (char *) (itup[i]), IndexTupleSize(itup[i]));

	/*
	 * Include a full page image of the child buf. (only necessary if a
	 * checkpoint happened since the child page was split)
	 */
	if (BufferIsValid(leftchildbuf))
		XLogRegisterBuffer(1, leftchildbuf, REGBUF_STANDARD);

	recptr = XLogInsert(RM_GIST_ID, XLOG_GIST_PAGE_UPDATE);

	return recptr;
}