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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  forget_invalid_pages_db (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smgrcloseall () ; 

void
XLogDropDatabase(Oid dbid)
{
	/*
	 * This is unnecessarily heavy-handed, as it will close SMgrRelation
	 * objects for other databases as well. DROP DATABASE occurs seldom enough
	 * that it's not worth introducing a variant of smgrclose for just this
	 * purpose. XXX: Or should we rather leave the smgr entries dangling?
	 */
	smgrcloseall();

	forget_invalid_pages_db(dbid);
}