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
struct lola_stream {int /*<<< orphan*/  dsd; scalar_t__ prepared; int /*<<< orphan*/  substream; scalar_t__ paused; } ;
struct lola {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDPL ; 
 int /*<<< orphan*/  BDPU ; 
 int /*<<< orphan*/  CTL ; 
 int LOLA_DSD_CTL_DEIE ; 
 int LOLA_DSD_CTL_IOCE ; 
 int LOLA_DSD_CTL_SRST ; 
 int /*<<< orphan*/  LVI ; 
 int /*<<< orphan*/  lola_dsd_write (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lola_stream_clear_pending_irq (struct lola*,struct lola_stream*) ; 
 int /*<<< orphan*/  lola_stream_wait_for_fifo (struct lola*,struct lola_stream*,int) ; 
 int /*<<< orphan*/  lola_sync_pause (struct lola*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_srst_clear (struct lola*,struct lola_stream*) ; 

__attribute__((used)) static void lola_stream_reset(struct lola *chip, struct lola_stream *str)
{
	if (str->prepared) {
		if (str->paused)
			lola_sync_pause(chip, str->substream);
		str->prepared = 0;
		lola_dsd_write(chip, str->dsd, CTL,
			       LOLA_DSD_CTL_IOCE | LOLA_DSD_CTL_DEIE);
		lola_stream_wait_for_fifo(chip, str, false);
		lola_stream_clear_pending_irq(chip, str);
		lola_dsd_write(chip, str->dsd, CTL, LOLA_DSD_CTL_SRST);
		lola_dsd_write(chip, str->dsd, LVI, 0);
		lola_dsd_write(chip, str->dsd, BDPU, 0);
		lola_dsd_write(chip, str->dsd, BDPL, 0);
		wait_for_srst_clear(chip, str);
	}
}