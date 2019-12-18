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
struct snd_sof_dev {int dummy; } ;

/* Variables and functions */
 int snd_sof_dsp_read64 (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_write64 (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

bool snd_sof_dsp_update_bits64_unlocked(struct snd_sof_dev *sdev, u32 bar,
					u32 offset, u64 mask, u64 value)
{
	u64 old, new;

	old = snd_sof_dsp_read64(sdev, bar, offset);

	new = (old & ~mask) | (value & mask);

	if (old == new)
		return false;

	snd_sof_dsp_write64(sdev, bar, offset, new);

	return true;
}