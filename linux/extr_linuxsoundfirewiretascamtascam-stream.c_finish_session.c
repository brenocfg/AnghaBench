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
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_WRITE_QUADLET_REQUEST ; 
 scalar_t__ TSCM_ADDR_BASE ; 
 scalar_t__ TSCM_OFFSET_ISOC_RX_ON ; 
 scalar_t__ TSCM_OFFSET_START_STREAMING ; 
 int /*<<< orphan*/  snd_fw_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void finish_session(struct snd_tscm *tscm)
{
	__be32 reg;

	reg = 0;
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_START_STREAMING,
			   &reg, sizeof(reg), 0);

	reg = 0;
	snd_fw_transaction(tscm->unit, TCODE_WRITE_QUADLET_REQUEST,
			   TSCM_ADDR_BASE + TSCM_OFFSET_ISOC_RX_ON,
			   &reg, sizeof(reg), 0);

}