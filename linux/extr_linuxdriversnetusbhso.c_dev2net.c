#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hso_net {int dummy; } ;
struct TYPE_2__ {struct hso_net* dev_net; } ;
struct hso_device {TYPE_1__ port_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct hso_net *dev2net(struct hso_device *hso_dev)
{
	return hso_dev->port_data.dev_net;
}