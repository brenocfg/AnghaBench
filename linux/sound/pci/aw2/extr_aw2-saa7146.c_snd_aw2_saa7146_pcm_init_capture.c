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
struct snd_aw2_saa7146 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BaseA1_in ; 
 int /*<<< orphan*/  PageA1_in ; 
 int /*<<< orphan*/  ProtA1_in ; 
 int /*<<< orphan*/  WRITEREG (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 unsigned long snd_aw2_saa7146_get_limit (unsigned long) ; 

void snd_aw2_saa7146_pcm_init_capture(struct snd_aw2_saa7146 *chip,
				      int stream_number, unsigned long dma_addr,
				      unsigned long period_size,
				      unsigned long buffer_size)
{
	unsigned long dw_page, dw_limit;

	/* Configure DMA for substream
	   Configuration informations: ALSA has allocated continuous memory
	   pages. So we don't need to use MMU of saa7146.
	 */

	/* No MMU -> nothing to do with PageA1, we only configure the limit of
	   PageAx_out register */
	/* Disable MMU */
	dw_page = (0L << 11);

	/* Configure Limit for DMA access.
	   The limit register defines an address limit, which generates
	   an interrupt if passed by the actual PCI address pointer.
	   '0001' means an interrupt will be generated if the lower
	   6 bits (64 bytes) of the PCI address are zero. '0010'
	   defines a limit of 128 bytes, '0011' one of 256 bytes, and
	   so on up to 1 Mbyte defined by '1111'. This interrupt range
	   can be calculated as follows:
	   Range = 2^(5 + Limit) bytes.
	 */
	dw_limit = snd_aw2_saa7146_get_limit(period_size);
	dw_page |= (dw_limit << 4);

	if (stream_number == 0) {
		WRITEREG(dw_page, PageA1_in);

		/* Base address for DMA transfert. */
		/* This address has been reserved by ALSA. */
		/* This is a physical address */
		WRITEREG(dma_addr, BaseA1_in);

		/* Define upper limit for DMA access  */
		WRITEREG(dma_addr + buffer_size, ProtA1_in);
	} else {
		pr_err("aw2: snd_aw2_saa7146_pcm_init_capture: "
		       "Substream number is not 0 -> not managed\n");
	}
}