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
struct mtpav {scalar_t__ port; } ;

/* Variables and functions */
 scalar_t__ CREG ; 
 scalar_t__ SREG ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static u8 snd_mtpav_getreg(struct mtpav *chip, u16 reg)
{
	u8 rval = 0;

	if (reg == SREG) {
		rval = inb(chip->port + SREG);
		rval = (rval & 0xf8);
	} else if (reg == CREG) {
		rval = inb(chip->port + CREG);
		rval = (rval & 0x1c);
	}

	return rval;
}