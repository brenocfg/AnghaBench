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
 int /*<<< orphan*/  dprintf1 (char*,int,...) ; 
 int /*<<< orphan*/  expected_pk_fault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkey_access_deny (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdpkru () ; 
 int read_ptr (int*) ; 

void test_read_of_access_disabled_region(int *ptr, u16 pkey)
{
	int ptr_contents;

	dprintf1("disabling access to PKEY[%02d], doing read @ %p\n", pkey, ptr);
	rdpkru();
	pkey_access_deny(pkey);
	ptr_contents = read_ptr(ptr);
	dprintf1("*ptr: %d\n", ptr_contents);
	expected_pk_fault(pkey);
}