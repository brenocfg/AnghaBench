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
struct usb_interface {int dummy; } ;
struct i2400mu {int /*<<< orphan*/  i2400m; } ;

/* Variables and functions */
 int i2400m_post_reset (int /*<<< orphan*/ *) ; 
 struct i2400mu* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static
int i2400mu_post_reset(struct usb_interface *iface)
{
	struct i2400mu *i2400mu = usb_get_intfdata(iface);
	return i2400m_post_reset(&i2400mu->i2400m);
}