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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int CheckDateTokenTable (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ POSTGRES_EPOCH_JDATE ; 
 scalar_t__ UNIX_EPOCH_JDATE ; 
 scalar_t__ date2j (int,int,int) ; 
 int /*<<< orphan*/  datetktbl ; 
 int /*<<< orphan*/  deltatktbl ; 
 int /*<<< orphan*/  szdatetktbl ; 
 int /*<<< orphan*/  szdeltatktbl ; 

bool
CheckDateTokenTables(void)
{
	bool		ok = true;

	Assert(UNIX_EPOCH_JDATE == date2j(1970, 1, 1));
	Assert(POSTGRES_EPOCH_JDATE == date2j(2000, 1, 1));

	ok &= CheckDateTokenTable("datetktbl", datetktbl, szdatetktbl);
	ok &= CheckDateTokenTable("deltatktbl", deltatktbl, szdeltatktbl);
	return ok;
}