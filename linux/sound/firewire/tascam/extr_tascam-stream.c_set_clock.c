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
typedef  enum snd_tscm_clock { ____Placeholder_snd_tscm_clock } snd_tscm_clock ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CLOCK_CONFIG_MASK ; 
 int EAGAIN ; 
 int INT_MAX ; 
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 scalar_t__ TSCM_ADDR_BASE ; 
 scalar_t__ TSCM_OFFSET_CLOCK_STATUS ; 
 scalar_t__ TSCM_OFFSET_MULTIPLEX_MODE ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int get_clock (struct snd_tscm*,int*) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_clock(struct snd_tscm *tscm, unsigned int rate,
		     enum snd_tscm_clock clock)
{
	u32 data;
	__be32 reg;
	int err;

	err = get_clock(tscm, &data);
	if (err < 0)
		return err;
	data &= CLOCK_CONFIG_MASK;

	if (rate > 0) {
		data &= 0x000000ff;
		/* Base rate. */
		if ((rate % 44100) == 0) {
			data |= 0x00000100;
			/* Multiplier. */
			if (rate / 44100 == 2)
				data |= 0x00008000;
		} else if ((rate % 48000) == 0) {
			data |= 0x00000200;
			/* Multiplier. */
			if (rate / 48000 == 2)
				data |= 0x00008000;
		} else {
			return -EAGAIN;
		}
	}

	if (clock != INT_MAX) {
		data &= 0x0000ff00;
		data |= clock + 1;
	}

	reg = cpu_to_be32(data);

	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_CLOCK_STATUS,
				 &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	if (data & 0x00008000)
		reg = cpu_to_be32(0x0000001a);
	else
		reg = cpu_to_be32(0x0000000d);

	return snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				  TSCM_ADDR_BASE + TSCM_OFFSET_MULTIPLEX_MODE,
				  &reg, sizeof(reg), 0);
}