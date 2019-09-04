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
typedef  int u8 ;
typedef  int u32 ;
struct snd_galaxy {int config; scalar_t__ config_port; } ;

/* Variables and functions */
 int GALAXY_CONFIG_MASK ; 
 int GALAXY_CONFIG_SIZE ; 
 int /*<<< orphan*/  galaxy_set_config (struct snd_galaxy*,int) ; 
 int ioread8 (scalar_t__) ; 

__attribute__((used)) static void galaxy_config(struct snd_galaxy *galaxy, u32 config)
{
	int i;

	for (i = GALAXY_CONFIG_SIZE; i; i--) {
		u8 tmp = ioread8(galaxy->config_port + i - 1);
		galaxy->config = (galaxy->config << 8) | tmp;
	}
	config |= galaxy->config & GALAXY_CONFIG_MASK;
	galaxy_set_config(galaxy, config);
}