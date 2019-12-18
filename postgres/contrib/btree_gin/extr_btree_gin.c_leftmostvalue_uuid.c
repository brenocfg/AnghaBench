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
typedef  int /*<<< orphan*/  pg_uuid_t ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  UUIDPGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static Datum
leftmostvalue_uuid(void)
{
	/*
	 * palloc0 will create the UUID with all zeroes:
	 * "00000000-0000-0000-0000-000000000000"
	 */
	pg_uuid_t  *retval = (pg_uuid_t *) palloc0(sizeof(pg_uuid_t));

	return UUIDPGetDatum(retval);
}