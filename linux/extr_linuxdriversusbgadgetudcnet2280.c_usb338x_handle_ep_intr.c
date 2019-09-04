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
typedef  size_t u32 ;
struct net2280 {int /*<<< orphan*/ * ep; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 size_t BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ep_bit ; 
 int /*<<< orphan*/  handle_ep_small (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb338x_handle_ep_intr(struct net2280 *dev, u32 stat0)
{
	u32 index;
	u32 bit;

	for (index = 0; index < ARRAY_SIZE(ep_bit); index++) {
		bit = BIT(ep_bit[index]);

		if (!stat0)
			break;

		if (!(stat0 & bit))
			continue;

		stat0 &= ~bit;

		handle_ep_small(&dev->ep[index]);
	}
}