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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  atomic_long_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ICMP6_MIB_MAX ; 
 int atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __snmp6_fill_statsdev(u64 *stats, atomic_long_t *mib,
					int bytes)
{
	int i;
	int pad = bytes - sizeof(u64) * ICMP6_MIB_MAX;
	BUG_ON(pad < 0);

	/* Use put_unaligned() because stats may not be aligned for u64. */
	put_unaligned(ICMP6_MIB_MAX, &stats[0]);
	for (i = 1; i < ICMP6_MIB_MAX; i++)
		put_unaligned(atomic_long_read(&mib[i]), &stats[i]);

	memset(&stats[ICMP6_MIB_MAX], 0, pad);
}