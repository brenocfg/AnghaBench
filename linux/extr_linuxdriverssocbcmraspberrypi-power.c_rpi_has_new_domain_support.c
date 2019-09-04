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
struct rpi_power_domains {int /*<<< orphan*/  fw; } ;
struct rpi_power_domain_packet {int /*<<< orphan*/  on; int /*<<< orphan*/  domain; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
 int /*<<< orphan*/  RPI_FIRMWARE_GET_DOMAIN_STATE ; 
 int /*<<< orphan*/  RPI_POWER_DOMAIN_ARM ; 
 int rpi_firmware_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpi_power_domain_packet*,int) ; 

__attribute__((used)) static bool
rpi_has_new_domain_support(struct rpi_power_domains *rpi_domains)
{
	struct rpi_power_domain_packet packet;
	int ret;

	packet.domain = RPI_POWER_DOMAIN_ARM;
	packet.on = ~0;

	ret = rpi_firmware_property(rpi_domains->fw,
				    RPI_FIRMWARE_GET_DOMAIN_STATE,
				    &packet, sizeof(packet));

	return ret == 0 && packet.on != ~0;
}