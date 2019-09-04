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
struct snd_ff {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FF400_FETCH_PCM_FRAMES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TCODE_WRITE_BLOCK_REQUEST ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ff400_switch_fetching_mode(struct snd_ff *ff, bool enable)
{
	__le32 *reg;
	int i;
	int err;

	reg = kcalloc(18, sizeof(__le32), GFP_KERNEL);
	if (reg == NULL)
		return -ENOMEM;

	if (!enable) {
		/*
		 * Each quadlet is corresponding to data channels in a data
		 * blocks in reverse order. Precisely, quadlets for available
		 * data channels should be enabled. Here, I take second best
		 * to fetch PCM frames from all of data channels regardless of
		 * stf.
		 */
		for (i = 0; i < 18; ++i)
			reg[i] = cpu_to_le32(0x00000001);
	}

	err = snd_fw_transaction(ff->unit, TCODE_WRITE_BLOCK_REQUEST,
				 FF400_FETCH_PCM_FRAMES, reg,
				 sizeof(__le32) * 18, 0);
	kfree(reg);
	return err;
}