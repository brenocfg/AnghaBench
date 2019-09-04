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

__attribute__((used)) static inline void dpaa_flush(void *p)
{
	/*
	 * Only PPC needs to flush the cache currently - on ARM the mapping
	 * is non cacheable
	 */
#ifdef CONFIG_PPC
	flush_dcache_range((unsigned long)p, (unsigned long)p+64);
#endif
}