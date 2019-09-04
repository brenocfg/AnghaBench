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
struct rme96 {scalar_t__ iobase; int /*<<< orphan*/  wcreg; } ;

/* Variables and functions */
 scalar_t__ RME96_IO_CONTROL_REGISTER ; 
#define  RME96_LARGE_BLOCK_SIZE 129 
#define  RME96_SMALL_BLOCK_SIZE 128 
 int /*<<< orphan*/  RME96_WCR_IDIS ; 
 int /*<<< orphan*/  RME96_WCR_ISEL ; 
 int /*<<< orphan*/  snd_BUG () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
snd_rme96_set_period_properties(struct rme96 *rme96,
				size_t period_bytes)
{
	switch (period_bytes) {
	case RME96_LARGE_BLOCK_SIZE:
		rme96->wcreg &= ~RME96_WCR_ISEL;
		break;
	case RME96_SMALL_BLOCK_SIZE:
		rme96->wcreg |= RME96_WCR_ISEL;
		break;
	default:
		snd_BUG();
		break;
	}
	rme96->wcreg &= ~RME96_WCR_IDIS;
	writel(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
}