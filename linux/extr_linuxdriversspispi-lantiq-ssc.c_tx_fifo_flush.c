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
struct lantiq_ssc_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTQ_SPI_TXFCON ; 
 int /*<<< orphan*/  LTQ_SPI_TXFCON_TXFLU ; 
 int /*<<< orphan*/  lantiq_ssc_maskl (struct lantiq_ssc_spi const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx_fifo_flush(const struct lantiq_ssc_spi *spi)
{
	lantiq_ssc_maskl(spi, 0, LTQ_SPI_TXFCON_TXFLU, LTQ_SPI_TXFCON);
}