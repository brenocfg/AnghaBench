#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t lo_buf_used; int writingBlob; scalar_t__ lo_buf; int /*<<< orphan*/  loFd; scalar_t__ connection; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;
typedef  TYPE_2__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ahprintf (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendByteaLiteralAHX (TYPE_1__*,unsigned char const*,size_t,TYPE_2__*) ; 
 TYPE_1__* createPQExpBuffer () ; 
 int /*<<< orphan*/  destroyPQExpBuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  fatal (char*,unsigned long,unsigned long) ; 
 size_t lo_write (scalar_t__,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  ngettext (char*,char*,size_t) ; 
 int /*<<< orphan*/  pg_log_debug (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static void
dump_lo_buf(ArchiveHandle *AH)
{
	if (AH->connection)
	{
		size_t		res;

		res = lo_write(AH->connection, AH->loFd, AH->lo_buf, AH->lo_buf_used);
		pg_log_debug(ngettext("wrote %lu byte of large object data (result = %lu)",
							  "wrote %lu bytes of large object data (result = %lu)",
							  AH->lo_buf_used),
					 (unsigned long) AH->lo_buf_used, (unsigned long) res);
		if (res != AH->lo_buf_used)
			fatal("could not write to large object (result: %lu, expected: %lu)",
				  (unsigned long) res, (unsigned long) AH->lo_buf_used);
	}
	else
	{
		PQExpBuffer buf = createPQExpBuffer();

		appendByteaLiteralAHX(buf,
							  (const unsigned char *) AH->lo_buf,
							  AH->lo_buf_used,
							  AH);

		/* Hack: turn off writingBlob so ahwrite doesn't recurse to here */
		AH->writingBlob = 0;
		ahprintf(AH, "SELECT pg_catalog.lowrite(0, %s);\n", buf->data);
		AH->writingBlob = 1;

		destroyPQExpBuffer(buf);
	}
	AH->lo_buf_used = 0;
}