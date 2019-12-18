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
struct snd_m3 {unsigned long iobase; int hv_config; } ;

/* Variables and functions */
 unsigned long ASSP_CONTROL_C ; 
 unsigned short ASSP_HOST_INT_ENABLE ; 
 unsigned short ASSP_INT_ENABLE ; 
 scalar_t__ HOST_INT_CTRL ; 
 unsigned long HOST_INT_STATUS ; 
 int HV_CTRL_ENABLE ; 
 unsigned short HV_INT_ENABLE ; 
 unsigned short inb (unsigned long) ; 
 int /*<<< orphan*/  outb (unsigned short,unsigned long) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

__attribute__((used)) static void
snd_m3_enable_ints(struct snd_m3 *chip)
{
	unsigned long io = chip->iobase;
	unsigned short val;

	/* TODO: MPU401 not supported yet */
	val = ASSP_INT_ENABLE /*| MPU401_INT_ENABLE*/;
	if (chip->hv_config & HV_CTRL_ENABLE)
		val |= HV_INT_ENABLE;
	outb(val, chip->iobase + HOST_INT_STATUS);
	outw(val, io + HOST_INT_CTRL);
	outb(inb(io + ASSP_CONTROL_C) | ASSP_HOST_INT_ENABLE,
	     io + ASSP_CONTROL_C);
}