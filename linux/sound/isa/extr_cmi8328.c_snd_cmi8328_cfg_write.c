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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static void snd_cmi8328_cfg_write(u16 port, u8 reg, u8 val)
{
	outb(0x43, port + 3);
	outb(0x21, port + 3);
	outb(reg, port + 3);
	outb(val, port + 3);	/* yes, value goes to the same port as index */
}