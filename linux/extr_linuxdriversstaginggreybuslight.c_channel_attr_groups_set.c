#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct led_classdev {TYPE_1__** groups; } ;
struct gb_channel {int flags; TYPE_1__** attr_groups; TYPE_1__* attr_group; int /*<<< orphan*/ ** attrs; } ;
struct TYPE_8__ {int /*<<< orphan*/  attr; } ;
struct TYPE_7__ {int /*<<< orphan*/  attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  attr; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** attrs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GB_LIGHT_CHANNEL_FADER ; 
 int GB_LIGHT_CHANNEL_MULTICOLOR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_4__ dev_attr_color ; 
 TYPE_3__ dev_attr_fade_in ; 
 TYPE_2__ dev_attr_fade_out ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int channel_attr_groups_set(struct gb_channel *channel,
				   struct led_classdev *cdev)
{
	int attr = 0;
	int size = 0;

	if (channel->flags & GB_LIGHT_CHANNEL_MULTICOLOR)
		size++;
	if (channel->flags & GB_LIGHT_CHANNEL_FADER)
		size += 2;

	if (!size)
		return 0;

	/* Set attributes based in the channel flags */
	channel->attrs = kcalloc(size + 1, sizeof(*channel->attrs), GFP_KERNEL);
	if (!channel->attrs)
		return -ENOMEM;
	channel->attr_group = kcalloc(1, sizeof(*channel->attr_group),
				      GFP_KERNEL);
	if (!channel->attr_group)
		return -ENOMEM;
	channel->attr_groups = kcalloc(2, sizeof(*channel->attr_groups),
				       GFP_KERNEL);
	if (!channel->attr_groups)
		return -ENOMEM;

	if (channel->flags & GB_LIGHT_CHANNEL_MULTICOLOR)
		channel->attrs[attr++] = &dev_attr_color.attr;
	if (channel->flags & GB_LIGHT_CHANNEL_FADER) {
		channel->attrs[attr++] = &dev_attr_fade_in.attr;
		channel->attrs[attr++] = &dev_attr_fade_out.attr;
	}

	channel->attr_group->attrs = channel->attrs;

	channel->attr_groups[0] = channel->attr_group;

	cdev->groups = channel->attr_groups;

	return 0;
}