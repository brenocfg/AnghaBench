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

/* Variables and functions */
 int GTIMEOUT ; 
 scalar_t__ TRM_S1040_GEN_STATUS ; 
 scalar_t__ TRM_S1040_GEN_TIMER ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void trms1040_wait_30us(unsigned long io_port)
{
	/* ScsiPortStallExecution(30); wait 30 us */
	outb(5, io_port + TRM_S1040_GEN_TIMER);
	while (!(inb(io_port + TRM_S1040_GEN_STATUS) & GTIMEOUT))
		/* nothing */ ;
}