#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_6__ {char* data; int len; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  appendBinaryStringInfo (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  enlargeStringInfo (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 int pg_ntoh32 (int /*<<< orphan*/ ) ; 
 scalar_t__ pq_getbytes (char*,int) ; 
 scalar_t__ pq_getstring (TYPE_1__*) ; 

int
GetOldFunctionMessage(StringInfo buf)
{
	int32		ibuf;
	int			nargs;

	/* Dummy string argument */
	if (pq_getstring(buf))
		return EOF;
	/* Function OID */
	if (pq_getbytes((char *) &ibuf, 4))
		return EOF;
	appendBinaryStringInfo(buf, (char *) &ibuf, 4);
	/* Number of arguments */
	if (pq_getbytes((char *) &ibuf, 4))
		return EOF;
	appendBinaryStringInfo(buf, (char *) &ibuf, 4);
	nargs = pg_ntoh32(ibuf);
	/* For each argument ... */
	while (nargs-- > 0)
	{
		int			argsize;

		/* argsize */
		if (pq_getbytes((char *) &ibuf, 4))
			return EOF;
		appendBinaryStringInfo(buf, (char *) &ibuf, 4);
		argsize = pg_ntoh32(ibuf);
		if (argsize < -1)
		{
			/* FATAL here since no hope of regaining message sync */
			ereport(FATAL,
					(errcode(ERRCODE_PROTOCOL_VIOLATION),
					 errmsg("invalid argument size %d in function call message",
							argsize)));
		}
		/* and arg contents */
		if (argsize > 0)
		{
			/* Allocate space for arg */
			enlargeStringInfo(buf, argsize);
			/* And grab it */
			if (pq_getbytes(buf->data + buf->len, argsize))
				return EOF;
			buf->len += argsize;
			/* Place a trailing null per StringInfo convention */
			buf->data[buf->len] = '\0';
		}
	}
	return 0;
}