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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int jhash (void const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline u32 batadv_choose_orig(const void *data, u32 size)
{
	u32 hash = 0;

	hash = jhash(data, ETH_ALEN, hash);
	return hash % size;
}