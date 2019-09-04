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
typedef  int u8 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROM_CMD ; 
 int rtl92e_readb (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool _rtl92e_gpio_get_bit(struct net_device *dev, int no)
{
	u8 reg = rtl92e_readb(dev, EPROM_CMD);

	return (reg >> no) & 0x1;
}