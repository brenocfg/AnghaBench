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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rsi_hw {scalar_t__ rsi_dev; } ;
struct rsi_91x_sdiodev {scalar_t__ sdio_irq_task; int /*<<< orphan*/  pfunction; } ;

/* Variables and functions */
 scalar_t__ current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_f0_writeb (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_writeb (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*) ; 

int rsi_sdio_write_register(struct rsi_hw *adapter,
			    u8 function,
			    u32 addr,
			    u8 *data)
{
	struct rsi_91x_sdiodev *dev =
		(struct rsi_91x_sdiodev *)adapter->rsi_dev;
	int status = 0;

	if (likely(dev->sdio_irq_task != current))
		sdio_claim_host(dev->pfunction);

	if (function == 0)
		sdio_f0_writeb(dev->pfunction, *data, addr, &status);
	else
		sdio_writeb(dev->pfunction, *data, addr, &status);

	if (likely(dev->sdio_irq_task != current))
		sdio_release_host(dev->pfunction);

	return status;
}