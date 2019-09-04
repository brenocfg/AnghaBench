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
struct rme96 {int wcreg; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ RME96_IO_CONTROL_REGISTER ; 
 int RME96_WCR_PD ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void
snd_rme96_reset_dac(struct rme96 *rme96)
{
	writel(rme96->wcreg | RME96_WCR_PD,
	       rme96->iobase + RME96_IO_CONTROL_REGISTER);
	writel(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
}