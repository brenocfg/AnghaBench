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
typedef  int u64 ;

/* Variables and functions */
 int HASH_TBL_ADDR_AUTOINC ; 

__attribute__((used)) static u64 hash_addr_regval(unsigned long index, unsigned long num_entries)
{
	return (u64)index | (num_entries == 1 ? HASH_TBL_ADDR_AUTOINC : 0);
}