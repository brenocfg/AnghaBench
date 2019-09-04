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
struct orc_host {scalar_t__ base; } ;

/* Variables and functions */
 int HOSTSTOP ; 
 scalar_t__ ORC_HCTRL ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static u8 wait_chip_ready(struct orc_host * host)
{
	int i;

	for (i = 0; i < 10; i++) {	/* Wait 1 second for report timeout     */
		if (inb(host->base + ORC_HCTRL) & HOSTSTOP)	/* Wait HOSTSTOP set */
			return 1;
		msleep(100);
	}
	return 0;
}