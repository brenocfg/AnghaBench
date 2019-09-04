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
struct usbnet {scalar_t__* data; } ;
struct sierra_net_data {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct sierra_net_data *sierra_net_get_private(struct usbnet *dev)
{
	return (struct sierra_net_data *)dev->data[0];
}