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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * bytes; } ;
struct RAID_CONTEXT_G35 {TYPE_1__ u; } ;

/* Variables and functions */
 int NUM_SGE_MASK_LOWER ; 
 int NUM_SGE_MASK_UPPER ; 
 int NUM_SGE_SHIFT_UPPER ; 

__attribute__((used)) static inline void set_num_sge(struct RAID_CONTEXT_G35 *rctx_g35,
			       u16 sge_count)
{
	rctx_g35->u.bytes[0] = (u8)(sge_count & NUM_SGE_MASK_LOWER);
	rctx_g35->u.bytes[1] |= (u8)((sge_count >> NUM_SGE_SHIFT_UPPER)
							& NUM_SGE_MASK_UPPER);
}