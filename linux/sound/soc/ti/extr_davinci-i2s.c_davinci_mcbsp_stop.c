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
typedef  int u32 ;
struct davinci_mcbsp_dev {int dummy; } ;

/* Variables and functions */
 int DAVINCI_MCBSP_SPCR_FRST ; 
 int DAVINCI_MCBSP_SPCR_GRST ; 
 int /*<<< orphan*/  DAVINCI_MCBSP_SPCR_REG ; 
 int DAVINCI_MCBSP_SPCR_RRST ; 
 int DAVINCI_MCBSP_SPCR_XRST ; 
 int davinci_mcbsp_read_reg (struct davinci_mcbsp_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_mcbsp_write_reg (struct davinci_mcbsp_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  toggle_clock (struct davinci_mcbsp_dev*,int) ; 

__attribute__((used)) static void davinci_mcbsp_stop(struct davinci_mcbsp_dev *dev, int playback)
{
	u32 spcr;

	/* Reset transmitter/receiver and sample rate/frame sync generators */
	spcr = davinci_mcbsp_read_reg(dev, DAVINCI_MCBSP_SPCR_REG);
	spcr &= ~(DAVINCI_MCBSP_SPCR_GRST | DAVINCI_MCBSP_SPCR_FRST);
	spcr &= playback ? ~DAVINCI_MCBSP_SPCR_XRST : ~DAVINCI_MCBSP_SPCR_RRST;
	davinci_mcbsp_write_reg(dev, DAVINCI_MCBSP_SPCR_REG, spcr);
	toggle_clock(dev, playback);
}