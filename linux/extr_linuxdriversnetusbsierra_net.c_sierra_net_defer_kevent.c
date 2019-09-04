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
struct usbnet {int dummy; } ;
struct sierra_net_data {int /*<<< orphan*/  sierra_net_kevent; int /*<<< orphan*/  kevent_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 struct sierra_net_data* sierra_net_get_private (struct usbnet*) ; 

__attribute__((used)) static void sierra_net_defer_kevent(struct usbnet *dev, int work)
{
	struct sierra_net_data *priv = sierra_net_get_private(dev);

	set_bit(work, &priv->kevent_flags);
	schedule_work(&priv->sierra_net_kevent);
}