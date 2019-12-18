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
typedef  int u32 ;

/* Variables and functions */
 int DEVID_HASH_MASK ; 
 int jhash_2words (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 devid_hashfn(u64 idx)
{
	return jhash_2words(idx, idx >> 32, 0) & DEVID_HASH_MASK;
}