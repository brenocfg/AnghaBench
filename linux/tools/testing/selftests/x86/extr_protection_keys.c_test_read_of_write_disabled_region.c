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
 int /*<<< orphan*/  dprintf1 (char*,...) ; 
 int /*<<< orphan*/  pkey_write_deny (int /*<<< orphan*/ ) ; 
 int read_ptr (int*) ; 

void test_read_of_write_disabled_region(int *ptr, u16 pkey)
{
	int ptr_contents;

	dprintf1("disabling write access to PKEY[1], doing read\n");
	pkey_write_deny(pkey);
	ptr_contents = read_ptr(ptr);
	dprintf1("*ptr: %d\n", ptr_contents);
	dprintf1("\n");
}