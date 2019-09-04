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
 scalar_t__ KDB_DEBUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASK ; 
 scalar_t__* __env ; 
 int __nenv ; 
 scalar_t__ kdb_flags ; 
 int /*<<< orphan*/  kdb_printf (char*,scalar_t__) ; 

__attribute__((used)) static int kdb_env(int argc, const char **argv)
{
	int i;

	for (i = 0; i < __nenv; i++) {
		if (__env[i])
			kdb_printf("%s\n", __env[i]);
	}

	if (KDB_DEBUG(MASK))
		kdb_printf("KDBFLAGS=0x%x\n", kdb_flags);

	return 0;
}