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
struct sun4i_spi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_FIFO_STA_REG ; 
 int SUN4I_FIFO_STA_TF_CNT_BITS ; 
 int SUN4I_FIFO_STA_TF_CNT_MASK ; 
 int sun4i_spi_read (struct sun4i_spi*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 sun4i_spi_get_tx_fifo_count(struct sun4i_spi *sspi)
{
	u32 reg = sun4i_spi_read(sspi, SUN4I_FIFO_STA_REG);

	reg >>= SUN4I_FIFO_STA_TF_CNT_BITS;

	return reg & SUN4I_FIFO_STA_TF_CNT_MASK;
}