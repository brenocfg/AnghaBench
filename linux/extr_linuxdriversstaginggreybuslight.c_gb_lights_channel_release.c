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
struct gb_channel {int releasing; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_lights_channel_free (struct gb_channel*) ; 
 int /*<<< orphan*/  gb_lights_channel_unregister (struct gb_channel*) ; 

__attribute__((used)) static void gb_lights_channel_release(struct gb_channel *channel)
{
	channel->releasing = true;

	gb_lights_channel_unregister(channel);

	gb_lights_channel_free(channel);
}