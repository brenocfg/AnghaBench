#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {scalar_t__ Pfdebug; int /*<<< orphan*/  noticeHooks; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,unsigned long,int) ; 
 int /*<<< orphan*/  pg_hton16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_hton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqInternalNotice (int /*<<< orphan*/ *,char*,unsigned long) ; 
 int /*<<< orphan*/  pqPutMsgBytes (char const*,int,TYPE_1__*) ; 

int
pqPutInt(int value, size_t bytes, PGconn *conn)
{
	uint16		tmp2;
	uint32		tmp4;

	switch (bytes)
	{
		case 2:
			tmp2 = pg_hton16((uint16) value);
			if (pqPutMsgBytes((const char *) &tmp2, 2, conn))
				return EOF;
			break;
		case 4:
			tmp4 = pg_hton32((uint32) value);
			if (pqPutMsgBytes((const char *) &tmp4, 4, conn))
				return EOF;
			break;
		default:
			pqInternalNotice(&conn->noticeHooks,
							 "integer of size %lu not supported by pqPutInt",
							 (unsigned long) bytes);
			return EOF;
	}

	if (conn->Pfdebug)
		fprintf(conn->Pfdebug, "To backend (%lu#)> %d\n", (unsigned long) bytes, value);

	return 0;
}