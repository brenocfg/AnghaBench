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
struct TYPE_3__ {scalar_t__ status; scalar_t__ asyncStatus; int /*<<< orphan*/  xactStatus; } ;
typedef  TYPE_1__ PGconn ;
typedef  int /*<<< orphan*/  PGTransactionStatusType ;

/* Variables and functions */
 scalar_t__ CONNECTION_OK ; 
 scalar_t__ PGASYNC_IDLE ; 
 int /*<<< orphan*/  PQTRANS_ACTIVE ; 
 int /*<<< orphan*/  PQTRANS_UNKNOWN ; 

PGTransactionStatusType
PQtransactionStatus(const PGconn *conn)
{
	if (!conn || conn->status != CONNECTION_OK)
		return PQTRANS_UNKNOWN;
	if (conn->asyncStatus != PGASYNC_IDLE)
		return PQTRANS_ACTIVE;
	return conn->xactStatus;
}