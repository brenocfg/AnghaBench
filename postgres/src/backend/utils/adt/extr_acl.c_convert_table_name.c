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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * makeRangeVarFromNameList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textToQualifiedNameList (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Oid
convert_table_name(text *tablename)
{
	RangeVar   *relrv;

	relrv = makeRangeVarFromNameList(textToQualifiedNameList(tablename));

	/* We might not even have permissions on this relation; don't lock it. */
	return RangeVarGetRelid(relrv, NoLock, false);
}