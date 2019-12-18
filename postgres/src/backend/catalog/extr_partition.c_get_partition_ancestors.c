#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  InheritsRelationId ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  get_partition_ancestors_worker (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

List *
get_partition_ancestors(Oid relid)
{
	List	   *result = NIL;
	Relation	inhRel;

	inhRel = table_open(InheritsRelationId, AccessShareLock);

	get_partition_ancestors_worker(inhRel, relid, &result);

	table_close(inhRel, AccessShareLock);

	return result;
}