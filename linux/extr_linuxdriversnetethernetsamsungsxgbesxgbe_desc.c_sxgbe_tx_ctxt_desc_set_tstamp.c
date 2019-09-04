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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
typedef  void* u32 ;
struct sxgbe_tx_ctxt_desc {void* tstamp_hi; void* tstamp_lo; scalar_t__ ostc; } ;

/* Variables and functions */

__attribute__((used)) static void sxgbe_tx_ctxt_desc_set_tstamp(struct sxgbe_tx_ctxt_desc *p,
					  u8 ostc_enable, u64 tstamp)
{
	if (ostc_enable) {
		p->ostc = ostc_enable;
		p->tstamp_lo = (u32) tstamp;
		p->tstamp_hi = (u32) (tstamp>>32);
	}
}