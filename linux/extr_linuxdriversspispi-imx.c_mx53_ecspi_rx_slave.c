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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct spi_imx_data {int slave_burst; int remainder; scalar_t__ rx_buf; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MXC_CSPIRXDATA ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void mx53_ecspi_rx_slave(struct spi_imx_data *spi_imx)
{
	u32 val = be32_to_cpu(readl(spi_imx->base + MXC_CSPIRXDATA));

	if (spi_imx->rx_buf) {
		int n_bytes = spi_imx->slave_burst % sizeof(val);

		if (!n_bytes)
			n_bytes = sizeof(val);

		memcpy(spi_imx->rx_buf,
		       ((u8 *)&val) + sizeof(val) - n_bytes, n_bytes);

		spi_imx->rx_buf += n_bytes;
		spi_imx->slave_burst -= n_bytes;
	}

	spi_imx->remainder -= sizeof(u32);
}