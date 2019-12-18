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
struct TYPE_4__ {scalar_t__ outMsgEnd; scalar_t__ outBuffer; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 scalar_t__ pqCheckOutBufferSpace (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static int
pqPutMsgBytes(const void *buf, size_t len, PGconn *conn)
{
	/* make sure there is room for it */
	if (pqCheckOutBufferSpace(conn->outMsgEnd + len, conn))
		return EOF;
	/* okay, save the data */
	memcpy(conn->outBuffer + conn->outMsgEnd, buf, len);
	conn->outMsgEnd += len;
	/* no Pfdebug call here, caller should do it */
	return 0;
}