#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  db; int /*<<< orphan*/  tr; int /*<<< orphan*/  isc_status; } ;
typedef  TYPE_1__ pdo_firebird_db_handle ;
struct TYPE_6__ {int transaction_flags; scalar_t__ driver_data; } ;
typedef  TYPE_2__ pdo_dbh_t ;

/* Variables and functions */
 int PDO_TRANS_ABORT ; 
 int PDO_TRANS_ACCESS_MODE ; 
 int PDO_TRANS_CONFLICT_RESOLUTION ; 
 int PDO_TRANS_ISOLATION_LEVEL ; 
 int PDO_TRANS_READONLY ; 
 int PDO_TRANS_READWRITE ; 
 int PDO_TRANS_READ_COMMITTED ; 
 int PDO_TRANS_READ_UNCOMMITTED ; 
 int PDO_TRANS_REPEATABLE_READ ; 
 int PDO_TRANS_RETRY ; 
 int PDO_TRANS_SERIALIZABLE ; 
 int /*<<< orphan*/  RECORD_ERROR (TYPE_2__*) ; 
 scalar_t__ isc_start_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,unsigned short,char*) ; 
 int /*<<< orphan*/  isc_tpb_concurrency ; 
 int /*<<< orphan*/  isc_tpb_consistency ; 
 int /*<<< orphan*/  isc_tpb_no_rec_version ; 
 int /*<<< orphan*/  isc_tpb_nowait ; 
 int /*<<< orphan*/  isc_tpb_read ; 
 void* isc_tpb_read_committed ; 
 int /*<<< orphan*/  isc_tpb_rec_version ; 
 char isc_tpb_version3 ; 
 int /*<<< orphan*/  isc_tpb_wait ; 
 int /*<<< orphan*/  isc_tpb_write ; 

__attribute__((used)) static int firebird_handle_begin(pdo_dbh_t *dbh) /* {{{ */
{
	pdo_firebird_db_handle *H = (pdo_firebird_db_handle *)dbh->driver_data;
	char tpb[8] = { isc_tpb_version3 }, *ptpb = tpb+1;
#if abies_0
	if (dbh->transaction_flags & PDO_TRANS_ISOLATION_LEVEL) {
		if (dbh->transaction_flags & PDO_TRANS_READ_UNCOMMITTED) {
			/* this is a poor fit, but it's all we have */
			*ptpb++ = isc_tpb_read_committed;
			*ptpb++ = isc_tpb_rec_version;
			dbh->transaction_flags &= ~(PDO_TRANS_ISOLATION_LEVEL^PDO_TRANS_READ_UNCOMMITTED);
		} else if (dbh->transaction_flags & PDO_TRANS_READ_COMMITTED) {
			*ptpb++ = isc_tpb_read_committed;
			*ptpb++ = isc_tpb_no_rec_version;
			dbh->transaction_flags &= ~(PDO_TRANS_ISOLATION_LEVEL^PDO_TRANS_READ_COMMITTED);
		} else if (dbh->transaction_flags & PDO_TRANS_REPEATABLE_READ) {
			*ptpb++ = isc_tpb_concurrency;
			dbh->transaction_flags &= ~(PDO_TRANS_ISOLATION_LEVEL^PDO_TRANS_REPEATABLE_READ);
		} else {
			*ptpb++ = isc_tpb_consistency;
			dbh->transaction_flags &= ~(PDO_TRANS_ISOLATION_LEVEL^PDO_TRANS_SERIALIZABLE);
		}
	}

	if (dbh->transaction_flags & PDO_TRANS_ACCESS_MODE) {
		if (dbh->transaction_flags & PDO_TRANS_READONLY) {
			*ptpb++ = isc_tpb_read;
			dbh->transaction_flags &= ~(PDO_TRANS_ACCESS_MODE^PDO_TRANS_READONLY);
		} else {
			*ptpb++ = isc_tpb_write;
			dbh->transaction_flags &= ~(PDO_TRANS_ACCESS_MODE^PDO_TRANS_READWRITE);
		}
	}

	if (dbh->transaction_flags & PDO_TRANS_CONFLICT_RESOLUTION) {
		if (dbh->transaction_flags & PDO_TRANS_RETRY) {
			*ptpb++ = isc_tpb_wait;
			dbh->transaction_flags &= ~(PDO_TRANS_CONFLICT_RESOLUTION^PDO_TRANS_RETRY);
		} else {
			*ptpb++ = isc_tpb_nowait;
			dbh->transaction_flags &= ~(PDO_TRANS_CONFLICT_RESOLUTION^PDO_TRANS_ABORT);
		}
	}
#endif
	if (isc_start_transaction(H->isc_status, &H->tr, 1, &H->db, (unsigned short)(ptpb-tpb), tpb)) {
		RECORD_ERROR(dbh);
		return 0;
	}
	return 1;
}