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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct xgene_pmu_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_pmu_write_counter32 (struct xgene_pmu_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
xgene_pmu_write_counter64(struct xgene_pmu_dev *pmu_dev, int idx, u64 val)
{
	u32 cnt_lo, cnt_hi;

	cnt_hi = upper_32_bits(val);
	cnt_lo = lower_32_bits(val);

	/* v3 has 64-bit counter registers composed by 2 32-bit registers */
	xgene_pmu_write_counter32(pmu_dev, 2 * idx, cnt_lo);
	xgene_pmu_write_counter32(pmu_dev, 2 * idx + 1, cnt_hi);
}