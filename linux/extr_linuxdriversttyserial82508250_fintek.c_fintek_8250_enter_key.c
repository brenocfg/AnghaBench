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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ ADDR_PORT ; 
 int EBUSY ; 
 int /*<<< orphan*/  EXIT_KEY ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  request_muxed_region (scalar_t__,int,char*) ; 

__attribute__((used)) static int fintek_8250_enter_key(u16 base_port, u8 key)
{
	if (!request_muxed_region(base_port, 2, "8250_fintek"))
		return -EBUSY;

	/* Force to deactive all SuperIO in this base_port */
	outb(EXIT_KEY, base_port + ADDR_PORT);

	outb(key, base_port + ADDR_PORT);
	outb(key, base_port + ADDR_PORT);
	return 0;
}