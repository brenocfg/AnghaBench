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
struct brcms_c_info {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_b_read_tsf (int /*<<< orphan*/ ,int*,int*) ; 

u64 brcms_c_tsf_get(struct brcms_c_info *wlc)
{
	u32 tsf_h, tsf_l;
	u64 tsf;

	brcms_b_read_tsf(wlc->hw, &tsf_l, &tsf_h);

	tsf = tsf_h;
	tsf <<= 32;
	tsf |= tsf_l;

	return tsf;
}