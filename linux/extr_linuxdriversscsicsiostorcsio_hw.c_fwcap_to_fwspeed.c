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
typedef  int fw_port_cap32_t ;

/* Variables and functions */
 int FW_PORT_CAP32_SPEED_100G ; 
 int FW_PORT_CAP32_SPEED_100M ; 
 int FW_PORT_CAP32_SPEED_10G ; 
 int FW_PORT_CAP32_SPEED_1G ; 
 int FW_PORT_CAP32_SPEED_200G ; 
 int FW_PORT_CAP32_SPEED_25G ; 
 int FW_PORT_CAP32_SPEED_400G ; 
 int FW_PORT_CAP32_SPEED_40G ; 
 int FW_PORT_CAP32_SPEED_50G ; 

fw_port_cap32_t fwcap_to_fwspeed(fw_port_cap32_t acaps)
{
	#define TEST_SPEED_RETURN(__caps_speed) \
		do { \
			if (acaps & FW_PORT_CAP32_SPEED_##__caps_speed) \
				return FW_PORT_CAP32_SPEED_##__caps_speed; \
		} while (0)

	TEST_SPEED_RETURN(400G);
	TEST_SPEED_RETURN(200G);
	TEST_SPEED_RETURN(100G);
	TEST_SPEED_RETURN(50G);
	TEST_SPEED_RETURN(40G);
	TEST_SPEED_RETURN(25G);
	TEST_SPEED_RETURN(10G);
	TEST_SPEED_RETURN(1G);
	TEST_SPEED_RETURN(100M);

	#undef TEST_SPEED_RETURN

	return 0;
}