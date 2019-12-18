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
struct TYPE_4__ {int /*<<< orphan*/  xactStatus; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  PQTRANS_IDLE ; 
 int /*<<< orphan*/  PQTRANS_INERROR ; 
 int /*<<< orphan*/  PQTRANS_INTRANS ; 
 int /*<<< orphan*/  PQTRANS_UNKNOWN ; 
 scalar_t__ pqGetc (char*,TYPE_1__*) ; 

__attribute__((used)) static int
getReadyForQuery(PGconn *conn)
{
	char		xact_status;

	if (pqGetc(&xact_status, conn))
		return EOF;
	switch (xact_status)
	{
		case 'I':
			conn->xactStatus = PQTRANS_IDLE;
			break;
		case 'T':
			conn->xactStatus = PQTRANS_INTRANS;
			break;
		case 'E':
			conn->xactStatus = PQTRANS_INERROR;
			break;
		default:
			conn->xactStatus = PQTRANS_UNKNOWN;
			break;
	}

	return 0;
}