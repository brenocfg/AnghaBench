#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hdac_device {TYPE_2__* bus; int /*<<< orphan*/  link_power_control; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* link_power ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (TYPE_2__*,int) ; 

int snd_hdac_link_power(struct hdac_device *codec, bool enable)
{
	if  (!codec->link_power_control)
		return 0;

	if  (codec->bus->ops->link_power)
		return codec->bus->ops->link_power(codec->bus, enable);
	else
		return -EINVAL;
}