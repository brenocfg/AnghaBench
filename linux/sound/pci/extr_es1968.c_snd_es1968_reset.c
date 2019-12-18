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
struct es1968 {scalar_t__ io_port; } ;

/* Variables and functions */
 scalar_t__ ESM_PORT_HOST_IRQ ; 
 int ESM_RESET_DIRECTSOUND ; 
 int ESM_RESET_MAESTRO ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void snd_es1968_reset(struct es1968 *chip)
{
	/* Reset */
	outw(ESM_RESET_MAESTRO | ESM_RESET_DIRECTSOUND,
	     chip->io_port + ESM_PORT_HOST_IRQ);
	udelay(10);
	outw(0x0000, chip->io_port + ESM_PORT_HOST_IRQ);
	udelay(10);
}