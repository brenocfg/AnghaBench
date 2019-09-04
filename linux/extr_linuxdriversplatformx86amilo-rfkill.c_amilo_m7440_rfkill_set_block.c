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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  M7440_PORT1 ; 
 int /*<<< orphan*/  M7440_PORT2 ; 
 scalar_t__ M7440_RADIO_OFF1 ; 
 scalar_t__ M7440_RADIO_OFF2 ; 
 scalar_t__ M7440_RADIO_ON1 ; 
 scalar_t__ M7440_RADIO_ON2 ; 
 scalar_t__ inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amilo_m7440_rfkill_set_block(void *data, bool blocked)
{
	u8 val1 = blocked ? M7440_RADIO_OFF1 : M7440_RADIO_ON1;
	u8 val2 = blocked ? M7440_RADIO_OFF2 : M7440_RADIO_ON2;

	outb(val1, M7440_PORT1);
	outb(val2, M7440_PORT2);

	/* Check whether the state has changed correctly */
	if (inb(M7440_PORT1) != val1 || inb(M7440_PORT2) != val2)
		return -EIO;

	return 0;
}