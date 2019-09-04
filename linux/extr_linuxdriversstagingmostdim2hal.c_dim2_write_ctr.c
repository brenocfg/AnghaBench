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
 int /*<<< orphan*/  dim2_write_ctr_mask (int,int const*,int const*) ; 

__attribute__((used)) static inline void dim2_write_ctr(u32 ctr_addr, const u32 *value)
{
	u32 const mask[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

	dim2_write_ctr_mask(ctr_addr, mask, value);
}