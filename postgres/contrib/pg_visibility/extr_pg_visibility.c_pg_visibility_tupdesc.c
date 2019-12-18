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
typedef  int /*<<< orphan*/  TupleDesc ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BOOLOID ; 
 int /*<<< orphan*/  BlessTupleDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateTemplateTupleDesc (scalar_t__) ; 
 int /*<<< orphan*/  INT8OID ; 
 int /*<<< orphan*/  TupleDescInitEntry (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static TupleDesc
pg_visibility_tupdesc(bool include_blkno, bool include_pd)
{
	TupleDesc	tupdesc;
	AttrNumber	maxattr = 2;
	AttrNumber	a = 0;

	if (include_blkno)
		++maxattr;
	if (include_pd)
		++maxattr;
	tupdesc = CreateTemplateTupleDesc(maxattr);
	if (include_blkno)
		TupleDescInitEntry(tupdesc, ++a, "blkno", INT8OID, -1, 0);
	TupleDescInitEntry(tupdesc, ++a, "all_visible", BOOLOID, -1, 0);
	TupleDescInitEntry(tupdesc, ++a, "all_frozen", BOOLOID, -1, 0);
	if (include_pd)
		TupleDescInitEntry(tupdesc, ++a, "pd_all_visible", BOOLOID, -1, 0);
	Assert(a == maxattr);

	return BlessTupleDesc(tupdesc);
}