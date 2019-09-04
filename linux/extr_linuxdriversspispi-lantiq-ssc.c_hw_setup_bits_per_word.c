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
typedef  unsigned int u32 ;
struct lantiq_ssc_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_SPI_CON ; 
 int /*<<< orphan*/  LTQ_SPI_CON_BM_M ; 
 unsigned int LTQ_SPI_CON_BM_S ; 
 int /*<<< orphan*/  lantiq_ssc_maskl (struct lantiq_ssc_spi const*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hw_setup_bits_per_word(const struct lantiq_ssc_spi *spi,
				   unsigned int bits_per_word)
{
	u32 bm;

	/* CON.BM value = bits_per_word - 1 */
	bm = (bits_per_word - 1) << LTQ_SPI_CON_BM_S;

	lantiq_ssc_maskl(spi, LTQ_SPI_CON_BM_M, bm, LTQ_SPI_CON);
}