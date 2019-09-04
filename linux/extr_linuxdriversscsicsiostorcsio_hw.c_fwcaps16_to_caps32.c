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
typedef  int /*<<< orphan*/  fw_port_cap32_t ;
typedef  int fw_port_cap16_t ;

/* Variables and functions */
 int /*<<< orphan*/  FW_PORT_CAP32_802_3_ASM_DIR ; 
 int /*<<< orphan*/  FW_PORT_CAP32_802_3_PAUSE ; 
 int /*<<< orphan*/  FW_PORT_CAP32_ANEG ; 
 int /*<<< orphan*/  FW_PORT_CAP32_FC_RX ; 
 int /*<<< orphan*/  FW_PORT_CAP32_FC_TX ; 
 int /*<<< orphan*/  FW_PORT_CAP32_FEC_BASER_RS ; 
 int /*<<< orphan*/  FW_PORT_CAP32_FEC_RS ; 
 int /*<<< orphan*/  FW_PORT_CAP32_MDIAUTO ; 
 int /*<<< orphan*/  FW_PORT_CAP32_MDISTRAIGHT ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_100G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_100M ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_10G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_1G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_25G ; 
 int /*<<< orphan*/  FW_PORT_CAP32_SPEED_40G ; 
 int FW_PORT_CAP_802_3_ASM_DIR ; 
 int FW_PORT_CAP_802_3_PAUSE ; 
 int FW_PORT_CAP_ANEG ; 
 int FW_PORT_CAP_FC_RX ; 
 int FW_PORT_CAP_FC_TX ; 
 int FW_PORT_CAP_FEC_BASER_RS ; 
 int FW_PORT_CAP_FEC_RS ; 
 int FW_PORT_CAP_MDIAUTO ; 
 int FW_PORT_CAP_MDISTRAIGHT ; 
 int FW_PORT_CAP_SPEED_100G ; 
 int FW_PORT_CAP_SPEED_100M ; 
 int FW_PORT_CAP_SPEED_10G ; 
 int FW_PORT_CAP_SPEED_1G ; 
 int FW_PORT_CAP_SPEED_25G ; 
 int FW_PORT_CAP_SPEED_40G ; 

fw_port_cap32_t fwcaps16_to_caps32(fw_port_cap16_t caps16)
{
	fw_port_cap32_t caps32 = 0;

	#define CAP16_TO_CAP32(__cap) \
		do { \
			if (caps16 & FW_PORT_CAP_##__cap) \
				caps32 |= FW_PORT_CAP32_##__cap; \
		} while (0)

	CAP16_TO_CAP32(SPEED_100M);
	CAP16_TO_CAP32(SPEED_1G);
	CAP16_TO_CAP32(SPEED_25G);
	CAP16_TO_CAP32(SPEED_10G);
	CAP16_TO_CAP32(SPEED_40G);
	CAP16_TO_CAP32(SPEED_100G);
	CAP16_TO_CAP32(FC_RX);
	CAP16_TO_CAP32(FC_TX);
	CAP16_TO_CAP32(ANEG);
	CAP16_TO_CAP32(MDIAUTO);
	CAP16_TO_CAP32(MDISTRAIGHT);
	CAP16_TO_CAP32(FEC_RS);
	CAP16_TO_CAP32(FEC_BASER_RS);
	CAP16_TO_CAP32(802_3_PAUSE);
	CAP16_TO_CAP32(802_3_ASM_DIR);

	#undef CAP16_TO_CAP32

	return caps32;
}