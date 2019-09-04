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
typedef  unsigned long u32 ;

/* Variables and functions */
 unsigned long DPAA_GENALLOC_OFF ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bm_bpalloc ; 
 unsigned long gen_pool_alloc (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int bm_alloc_bpid_range(u32 *result, u32 count)
{
	unsigned long addr;

	addr = gen_pool_alloc(bm_bpalloc, count);
	if (!addr)
		return -ENOMEM;

	*result = addr & ~DPAA_GENALLOC_OFF;

	return 0;
}