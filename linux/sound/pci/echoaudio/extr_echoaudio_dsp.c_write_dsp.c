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
typedef  int u32 ;
struct echoaudio {int bad_board; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHI32_DATA_REG ; 
 int CHI32_STATUS_HOST_WRITE_EMPTY ; 
 int /*<<< orphan*/  CHI32_STATUS_REG ; 
 int EIO ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int get_dsp_register (struct echoaudio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dsp_register (struct echoaudio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int write_dsp(struct echoaudio *chip, u32 data)
{
	u32 status, i;

	for (i = 0; i < 10000000; i++) {	/* timeout = 10s */
		status = get_dsp_register(chip, CHI32_STATUS_REG);
		if ((status & CHI32_STATUS_HOST_WRITE_EMPTY) != 0) {
			set_dsp_register(chip, CHI32_DATA_REG, data);
			wmb();			/* write it immediately */
			return 0;
		}
		udelay(1);
		cond_resched();
	}

	chip->bad_board = true;		/* Set true until DSP re-loaded */
	dev_dbg(chip->card->dev, "write_dsp: Set bad_board to true\n");
	return -EIO;
}