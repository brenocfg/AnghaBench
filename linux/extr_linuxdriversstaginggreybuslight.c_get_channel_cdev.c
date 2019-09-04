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
struct led_classdev {int dummy; } ;
struct gb_channel {struct led_classdev cled; } ;

/* Variables and functions */

__attribute__((used)) static struct led_classdev *get_channel_cdev(struct gb_channel *channel)
{
	return &channel->cled;
}