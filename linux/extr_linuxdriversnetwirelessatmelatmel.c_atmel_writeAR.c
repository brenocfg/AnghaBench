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
typedef  scalar_t__ u16 ;
struct net_device {scalar_t__ base_addr; } ;

/* Variables and functions */
 scalar_t__ AR ; 
 scalar_t__ inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void atmel_writeAR(struct net_device *dev, u16 data)
{
	int i;
	outw(data, dev->base_addr + AR);
	/* Address register appears to need some convincing..... */
	for (i = 0; data != inw(dev->base_addr + AR) && i < 10; i++)
		outw(data, dev->base_addr + AR);
}