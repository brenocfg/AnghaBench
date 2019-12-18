#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* xactStatus; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 void* PQTRANS_IDLE ; 
 void* PQTRANS_INERROR ; 
 void* PQTRANS_INTRANS ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
checkXactStatus(PGconn *conn, const char *cmdTag)
{
	if (strcmp(cmdTag, "BEGIN") == 0)
		conn->xactStatus = PQTRANS_INTRANS;
	else if (strcmp(cmdTag, "COMMIT") == 0)
		conn->xactStatus = PQTRANS_IDLE;
	else if (strcmp(cmdTag, "ROLLBACK") == 0)
		conn->xactStatus = PQTRANS_IDLE;
	else if (strcmp(cmdTag, "START TRANSACTION") == 0)	/* 7.3 only */
		conn->xactStatus = PQTRANS_INTRANS;

	/*
	 * Normally we get into INERROR state by detecting an Error message.
	 * However, if we see one of these tags then we know for sure the server
	 * is in abort state ...
	 */
	else if (strcmp(cmdTag, "*ABORT STATE*") == 0)	/* pre-7.3 only */
		conn->xactStatus = PQTRANS_INERROR;
}