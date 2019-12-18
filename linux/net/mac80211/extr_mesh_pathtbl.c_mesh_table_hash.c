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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __get_unaligned_cpu32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jhash_1word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mesh_table_hash(const void *addr, u32 len, u32 seed)
{
	/* Use last four bytes of hw addr as hash index */
	return jhash_1word(__get_unaligned_cpu32((u8 *)addr + 2), seed);
}