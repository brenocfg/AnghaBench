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
typedef  int uint64_t ;
typedef  scalar_t__ u_int ;
struct ahc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,scalar_t__,int) ; 

void
ahc_outq(struct ahc_softc *ahc, u_int port, uint64_t value)
{
	ahc_outb(ahc, port, value & 0xFF);
	ahc_outb(ahc, port+1, (value >> 8) & 0xFF);
	ahc_outb(ahc, port+2, (value >> 16) & 0xFF);
	ahc_outb(ahc, port+3, (value >> 24) & 0xFF);
	ahc_outb(ahc, port+4, (value >> 32) & 0xFF);
	ahc_outb(ahc, port+5, (value >> 40) & 0xFF);
	ahc_outb(ahc, port+6, (value >> 48) & 0xFF);
	ahc_outb(ahc, port+7, (value >> 56) & 0xFF);
}