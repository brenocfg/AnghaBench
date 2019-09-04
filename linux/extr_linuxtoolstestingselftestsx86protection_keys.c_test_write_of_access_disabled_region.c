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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  dprintf1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expected_pk_fault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_access_deny (int /*<<< orphan*/ ) ; 

void test_write_of_access_disabled_region(int *ptr, u16 pkey)
{
	dprintf1("disabling access to PKEY[%02d], doing write\n", pkey);
	pkey_access_deny(pkey);
	*ptr = __LINE__;
	expected_pk_fault(pkey);
}