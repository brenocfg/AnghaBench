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
 int KDB_BADADDR ; 
 int /*<<< orphan*/  KDB_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KDB_STATE_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KDB_STATE_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUPPRESS ; 
 int /*<<< orphan*/  kdb_printf (char*,unsigned long) ; 
 int probe_kernel_read (char*,char*,size_t) ; 

int kdb_getarea_size(void *res, unsigned long addr, size_t size)
{
	int ret = probe_kernel_read((char *)res, (char *)addr, size);
	if (ret) {
		if (!KDB_STATE(SUPPRESS)) {
			kdb_printf("kdb_getarea: Bad address 0x%lx\n", addr);
			KDB_STATE_SET(SUPPRESS);
		}
		ret = KDB_BADADDR;
	} else {
		KDB_STATE_CLEAR(SUPPRESS);
	}
	return ret;
}