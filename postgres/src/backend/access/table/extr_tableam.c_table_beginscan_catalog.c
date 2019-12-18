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
typedef  int uint32 ;
struct ScanKeyData {int dummy; } ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_7__ {TYPE_1__* rd_tableam; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* scan_begin ) (TYPE_2__*,int /*<<< orphan*/ ,int,struct ScanKeyData*,int /*<<< orphan*/ *,int) ;} ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  GetCatalogSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int SO_ALLOW_PAGEMODE ; 
 int SO_ALLOW_STRAT ; 
 int SO_ALLOW_SYNC ; 
 int SO_TEMP_SNAPSHOT ; 
 int SO_TYPE_SEQSCAN ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int,struct ScanKeyData*,int /*<<< orphan*/ *,int) ; 

TableScanDesc
table_beginscan_catalog(Relation relation, int nkeys, struct ScanKeyData *key)
{
	uint32		flags = SO_TYPE_SEQSCAN |
	SO_ALLOW_STRAT | SO_ALLOW_SYNC | SO_ALLOW_PAGEMODE | SO_TEMP_SNAPSHOT;
	Oid			relid = RelationGetRelid(relation);
	Snapshot	snapshot = RegisterSnapshot(GetCatalogSnapshot(relid));

	return relation->rd_tableam->scan_begin(relation, snapshot, nkeys, key,
											NULL, flags);
}