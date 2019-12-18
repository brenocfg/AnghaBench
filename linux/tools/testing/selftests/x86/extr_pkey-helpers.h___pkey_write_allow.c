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
 int /*<<< orphan*/  dprintf4 (char*,long) ; 
 long rdpkru () ; 
 int /*<<< orphan*/  wrpkru (long) ; 

__attribute__((used)) static inline void __pkey_write_allow(int pkey, int do_allow_write)
{
	long pkru = rdpkru();
	int bit = pkey * 2 + 1;

	if (do_allow_write)
		pkru &= (1<<bit);
	else
		pkru |= (1<<bit);

	wrpkru(pkru);
	dprintf4("pkru now: %08x\n", rdpkru());
}