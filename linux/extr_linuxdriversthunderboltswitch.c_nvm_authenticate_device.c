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
typedef  scalar_t__ u32 ;
struct tb_switch {int /*<<< orphan*/  dma_port; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int dma_port_flash_update_auth (int /*<<< orphan*/ ) ; 
 int dma_port_flash_update_auth_status (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  dma_port_power_cycle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  nvm_set_auth_status (struct tb_switch*,scalar_t__) ; 
 int /*<<< orphan*/  tb_sw_info (struct tb_switch*,char*) ; 
 int /*<<< orphan*/  tb_sw_warn (struct tb_switch*,char*) ; 

__attribute__((used)) static int nvm_authenticate_device(struct tb_switch *sw)
{
	int ret, retries = 10;

	ret = dma_port_flash_update_auth(sw->dma_port);
	if (ret && ret != -ETIMEDOUT)
		return ret;

	/*
	 * Poll here for the authentication status. It takes some time
	 * for the device to respond (we get timeout for a while). Once
	 * we get response the device needs to be power cycled in order
	 * to the new NVM to be taken into use.
	 */
	do {
		u32 status;

		ret = dma_port_flash_update_auth_status(sw->dma_port, &status);
		if (ret < 0 && ret != -ETIMEDOUT)
			return ret;
		if (ret > 0) {
			if (status) {
				tb_sw_warn(sw, "failed to authenticate NVM\n");
				nvm_set_auth_status(sw, status);
			}

			tb_sw_info(sw, "power cycling the switch now\n");
			dma_port_power_cycle(sw->dma_port);
			return 0;
		}

		msleep(500);
	} while (--retries);

	return -ETIMEDOUT;
}