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
struct lola_stream {int prepared; int index; int frags; int /*<<< orphan*/  dsd; } ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct lola_pcm {TYPE_1__ bdl; } ;
struct lola {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BDPL ; 
 int /*<<< orphan*/  BDPU ; 
 int /*<<< orphan*/  CTL ; 
 int EINVAL ; 
 int LOLA_BDL_ENTRY_SIZE ; 
 int LOLA_DSD_CTL_DEIE ; 
 int LOLA_DSD_CTL_IOCE ; 
 int LOLA_DSD_CTL_SRUN ; 
 int /*<<< orphan*/  LVI ; 
 int /*<<< orphan*/  lola_dsd_write (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lola_stream_clear_pending_irq (struct lola*,struct lola_stream*) ; 
 int lola_stream_wait_for_fifo (struct lola*,struct lola_stream*,int) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int lola_setup_controller(struct lola *chip, struct lola_pcm *pcm,
				 struct lola_stream *str)
{
	dma_addr_t bdl;

	if (str->prepared)
		return -EINVAL;

	/* set up BDL */
	bdl = pcm->bdl.addr + LOLA_BDL_ENTRY_SIZE * str->index;
	lola_dsd_write(chip, str->dsd, BDPL, (u32)bdl);
	lola_dsd_write(chip, str->dsd, BDPU, upper_32_bits(bdl));
	/* program the stream LVI (last valid index) of the BDL */
	lola_dsd_write(chip, str->dsd, LVI, str->frags - 1);
	lola_stream_clear_pending_irq(chip, str);

 	lola_dsd_write(chip, str->dsd, CTL,
		       LOLA_DSD_CTL_IOCE | LOLA_DSD_CTL_DEIE | LOLA_DSD_CTL_SRUN);

	str->prepared = 1;

	return lola_stream_wait_for_fifo(chip, str, true);
}