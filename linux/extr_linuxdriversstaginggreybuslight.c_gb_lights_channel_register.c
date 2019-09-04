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
struct gb_channel {int mode; } ;

/* Variables and functions */
 int GB_CHANNEL_MODE_TORCH ; 
 int __gb_lights_flash_led_register (struct gb_channel*) ; 
 int __gb_lights_led_register (struct gb_channel*) ; 
 int /*<<< orphan*/  is_channel_flash (struct gb_channel*) ; 

__attribute__((used)) static int gb_lights_channel_register(struct gb_channel *channel)
{
	/* Normal LED channel, just register in led classdev and we are done */
	if (!is_channel_flash(channel))
		return __gb_lights_led_register(channel);

	/*
	 * Flash Type need more work, register flash classdev, indicator as
	 * flash classdev, torch will be led classdev of the flash classdev.
	 */
	if (!(channel->mode & GB_CHANNEL_MODE_TORCH))
		return __gb_lights_flash_led_register(channel);

	return 0;
}