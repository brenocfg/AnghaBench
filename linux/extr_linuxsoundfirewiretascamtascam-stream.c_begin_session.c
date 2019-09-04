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
struct snd_tscm {int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  reg ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 scalar_t__ TSCM_ADDR_BASE ; 
 scalar_t__ TSCM_OFFSET_ISOC_RX_ON ; 
 scalar_t__ TSCM_OFFSET_ISOC_TX_ON ; 
 scalar_t__ TSCM_OFFSET_SET_OPTION ; 
 scalar_t__ TSCM_OFFSET_START_STREAMING ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int begin_session(struct snd_tscm *tscm)
{
	__be32 reg;
	int err;

	reg = cpu_to_be32(0x00000001);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_START_STREAMING,
				 &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	reg = cpu_to_be32(0x00000001);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_ISOC_RX_ON,
				 &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	/* Set an option for unknown purpose. */
	reg = cpu_to_be32(0x00002000);
	err = snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
				 TSCM_ADDR_BASE + TSCM_OFFSET_SET_OPTION,
				 &reg, sizeof(reg), 0);
	if (err < 0)
		return err;

	/* Start multiplexing PCM samples on packets. */
	reg = cpu_to_be32(0x00000001);
	return snd_fw_transaction(tscm->unit,
				  TCODE_WRITE_QUADLET_REQUEST,
				  TSCM_ADDR_BASE + TSCM_OFFSET_ISOC_TX_ON,
				  &reg, sizeof(reg), 0);
}