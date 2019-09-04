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
typedef  int /*<<< orphan*/  u8 ;
struct scatterlist {int dummy; } ;
struct rtsx_chip {int need_reinit; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int EIO ; 
 int MS_CARD ; 
 int /*<<< orphan*/  RTSX_CLR_DELINK (struct rtsx_chip*) ; 
 int /*<<< orphan*/  RTSX_STAT_ABORT ; 
 scalar_t__ RTSX_TST_DELINK (struct rtsx_chip*) ; 
 int SD_CARD ; 
 int XD_CARD ; 
 scalar_t__ rtsx_chk_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_reinit_cards (struct rtsx_chip*,int) ; 
 int rtsx_transfer_buf (struct rtsx_chip*,int /*<<< orphan*/ ,void*,size_t,int,int) ; 
 int rtsx_transfer_sglist_adma_partial (struct rtsx_chip*,int /*<<< orphan*/ ,struct scatterlist*,int,unsigned int*,unsigned int*,int,int,int) ; 

int rtsx_transfer_data_partial(struct rtsx_chip *chip, u8 card,
			       void *buf, size_t len, int use_sg,
			       unsigned int *index, unsigned int *offset,
			       enum dma_data_direction dma_dir, int timeout)
{
	int err = 0;

	/* don't transfer data during abort processing */
	if (rtsx_chk_stat(chip, RTSX_STAT_ABORT))
		return -EIO;

	if (use_sg) {
		struct scatterlist *sg = buf;

		err = rtsx_transfer_sglist_adma_partial(chip, card, sg, use_sg,
							index, offset, (int)len,
							dma_dir, timeout);
	} else {
		err = rtsx_transfer_buf(chip, card,
					buf, len, dma_dir, timeout);
	}
	if (err < 0) {
		if (RTSX_TST_DELINK(chip)) {
			RTSX_CLR_DELINK(chip);
			chip->need_reinit = SD_CARD | MS_CARD | XD_CARD;
			rtsx_reinit_cards(chip, 1);
		}
	}

	return err;
}