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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct cw1200_common {int /*<<< orphan*/  hwbus_priv; TYPE_1__* hwbus_ops; } ;
struct TYPE_2__ {int (* hwbus_memcpy_toio ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SDIO_ADDR17BIT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_REG_ADDR_TO_SDIO (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int __cw1200_reg_write(struct cw1200_common *priv, u16 addr,
				const void *buf, size_t buf_len, int buf_id)
{
	u16 addr_sdio;
	u32 sdio_reg_addr_17bit;

	/* Convert to SDIO Register Address */
	addr_sdio = SPI_REG_ADDR_TO_SDIO(addr);
	sdio_reg_addr_17bit = SDIO_ADDR17BIT(buf_id, 0, 0, addr_sdio);

	return priv->hwbus_ops->hwbus_memcpy_toio(priv->hwbus_priv,
						sdio_reg_addr_17bit,
						buf, buf_len);
}