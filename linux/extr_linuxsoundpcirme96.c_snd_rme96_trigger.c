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
struct rme96 {int rcreg; scalar_t__ iobase; int /*<<< orphan*/  wcreg; } ;

/* Variables and functions */
 scalar_t__ RME96_IO_CONFIRM_PLAY_IRQ ; 
 scalar_t__ RME96_IO_CONFIRM_REC_IRQ ; 
 scalar_t__ RME96_IO_CONTROL_REGISTER ; 
 scalar_t__ RME96_IO_RESET_PLAY_POS ; 
 scalar_t__ RME96_IO_RESET_REC_POS ; 
 int RME96_RCR_IRQ ; 
 int RME96_RCR_IRQ_2 ; 
 int RME96_TB_CLEAR_CAPTURE_IRQ ; 
 int RME96_TB_CLEAR_PLAYBACK_IRQ ; 
 int RME96_TB_RESET_CAPTUREPOS ; 
 int RME96_TB_RESET_PLAYPOS ; 
 int RME96_TB_START_CAPTURE ; 
 int RME96_TB_START_PLAYBACK ; 
 int RME96_TB_STOP_CAPTURE ; 
 int RME96_TB_STOP_PLAYBACK ; 
 int /*<<< orphan*/  RME96_WCR_START ; 
 int /*<<< orphan*/  RME96_WCR_START_2 ; 
 void* readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
snd_rme96_trigger(struct rme96 *rme96,
		  int op)
{
	if (op & RME96_TB_RESET_PLAYPOS)
		writel(0, rme96->iobase + RME96_IO_RESET_PLAY_POS);
	if (op & RME96_TB_RESET_CAPTUREPOS)
		writel(0, rme96->iobase + RME96_IO_RESET_REC_POS);
	if (op & RME96_TB_CLEAR_PLAYBACK_IRQ) {
		rme96->rcreg = readl(rme96->iobase + RME96_IO_CONTROL_REGISTER);
		if (rme96->rcreg & RME96_RCR_IRQ)
			writel(0, rme96->iobase + RME96_IO_CONFIRM_PLAY_IRQ);
	}
	if (op & RME96_TB_CLEAR_CAPTURE_IRQ) {
		rme96->rcreg = readl(rme96->iobase + RME96_IO_CONTROL_REGISTER);
		if (rme96->rcreg & RME96_RCR_IRQ_2)
			writel(0, rme96->iobase + RME96_IO_CONFIRM_REC_IRQ);
	}
	if (op & RME96_TB_START_PLAYBACK)
		rme96->wcreg |= RME96_WCR_START;
	if (op & RME96_TB_STOP_PLAYBACK)
		rme96->wcreg &= ~RME96_WCR_START;
	if (op & RME96_TB_START_CAPTURE)
		rme96->wcreg |= RME96_WCR_START_2;
	if (op & RME96_TB_STOP_CAPTURE)
		rme96->wcreg &= ~RME96_WCR_START_2;
	writel(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
}