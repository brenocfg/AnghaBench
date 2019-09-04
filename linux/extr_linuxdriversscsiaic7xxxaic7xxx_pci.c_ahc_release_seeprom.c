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
struct seeprom_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEPROM_OUTB (struct seeprom_descriptor*,int /*<<< orphan*/ ) ; 

void
ahc_release_seeprom(struct seeprom_descriptor *sd)
{
	/* Release access to the memory port and the serial EEPROM. */
	SEEPROM_OUTB(sd, 0);
}