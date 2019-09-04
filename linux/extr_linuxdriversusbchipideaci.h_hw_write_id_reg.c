#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int abs; } ;
struct ci_hdrc {TYPE_1__ hw_bank; } ;

/* Variables and functions */
 int ioread32 (int) ; 
 int /*<<< orphan*/  iowrite32 (int,int) ; 

__attribute__((used)) static inline void hw_write_id_reg(struct ci_hdrc *ci, u32 offset,
			    u32 mask, u32 data)
{
	if (~mask)
		data = (ioread32(ci->hw_bank.abs + offset) & ~mask)
			| (data & mask);

	iowrite32(data, ci->hw_bank.abs + offset);
}