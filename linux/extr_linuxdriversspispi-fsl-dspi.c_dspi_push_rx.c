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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct fsl_dspi {int bits_per_word; int bytes_per_word; scalar_t__ rx; } ;

/* Variables and functions */

__attribute__((used)) static void dspi_push_rx(struct fsl_dspi *dspi, u32 rxdata)
{
	if (!dspi->rx)
		return;

	/* Mask of undefined bits */
	rxdata &= (1 << dspi->bits_per_word) - 1;

	if (dspi->bytes_per_word == 1)
		*(u8 *)dspi->rx = rxdata;
	else if (dspi->bytes_per_word == 2)
		*(u16 *)dspi->rx = rxdata;
	else /* dspi->bytes_per_word == 4 */
		*(u32 *)dspi->rx = rxdata;
	dspi->rx += dspi->bytes_per_word;
}