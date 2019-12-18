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
struct snd_tscm {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CLOCK_STATUS_MASK ; 
 int EAGAIN ; 
 int /*<<< orphan*/  TCODE_READ_QUADLET_REQUEST ; 
 scalar_t__ TSCM_ADDR_BASE ; 
 scalar_t__ TSCM_OFFSET_CLOCK_STATUS ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_clock(struct snd_tscm *tscm, u32 *data)
{
	int trial = 0;
	__be32 reg;
	int err;

	while (trial++ < 5) {
		err = snd_fw_transaction(tscm->unit, TCODE_READ_QUADLET_REQUEST,
				TSCM_ADDR_BASE + TSCM_OFFSET_CLOCK_STATUS,
				&reg, sizeof(reg), 0);
		if (err < 0)
			return err;

		*data = be32_to_cpu(reg);
		if (*data & CLOCK_STATUS_MASK)
			break;

		// In intermediate state after changing clock status.
		msleep(50);
	}

	// Still in the intermediate state.
	if (trial >= 5)
		return -EAGAIN;

	return 0;
}