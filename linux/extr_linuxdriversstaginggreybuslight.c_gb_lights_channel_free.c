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
struct gb_channel {int /*<<< orphan*/  lock; int /*<<< orphan*/  mode_name; int /*<<< orphan*/  color_name; int /*<<< orphan*/  attr_groups; int /*<<< orphan*/  attr_group; int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_lights_channel_free(struct gb_channel *channel)
{
	kfree(channel->attrs);
	kfree(channel->attr_group);
	kfree(channel->attr_groups);
	kfree(channel->color_name);
	kfree(channel->mode_name);
	mutex_destroy(&channel->lock);
}