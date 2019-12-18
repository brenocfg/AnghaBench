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
typedef  int /*<<< orphan*/  u32 ;
struct sst_dsp {int dummy; } ;

/* Variables and functions */
 int sst_dsp_shim_read64_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_write64_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int) ; 

int sst_dsp_shim_update_bits64_unlocked(struct sst_dsp *sst, u32 offset,
				u64 mask, u64 value)
{
	bool change;
	u64 old, new;

	old = sst_dsp_shim_read64_unlocked(sst, offset);

	new = (old & (~mask)) | (value & mask);

	change = (old != new);
	if (change)
		sst_dsp_shim_write64_unlocked(sst, offset, new);

	return change;
}