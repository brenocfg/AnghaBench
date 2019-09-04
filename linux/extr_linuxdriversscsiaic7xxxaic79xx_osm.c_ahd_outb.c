#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ahd_softc {scalar_t__* tags; TYPE_1__* bshs; } ;
struct TYPE_2__ {scalar_t__ ioport; scalar_t__ maddr; } ;

/* Variables and functions */
 scalar_t__ BUS_SPACE_MEMIO ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

void
ahd_outb(struct ahd_softc * ahd, long port, uint8_t val)
{
	if (ahd->tags[0] == BUS_SPACE_MEMIO) {
		writeb(val, ahd->bshs[0].maddr + port);
	} else {
		outb(val, ahd->bshs[(port) >> 8].ioport + (port & 0xFF));
	}
	mb();
}