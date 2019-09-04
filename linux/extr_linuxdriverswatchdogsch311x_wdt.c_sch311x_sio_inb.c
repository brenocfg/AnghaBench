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
 int inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static inline int sch311x_sio_inb(int sio_config_port, int reg)
{
	outb(reg, sio_config_port);
	return inb(sio_config_port + 1);
}