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
struct rpmsg_channel_info {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* device_find_child (struct device*,struct rpmsg_channel_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpmsg_device_match ; 

struct device *rpmsg_find_device(struct device *parent,
				 struct rpmsg_channel_info *chinfo)
{
	return device_find_child(parent, chinfo, rpmsg_device_match);

}