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
struct spi_message {int dummy; } ;
struct spi_controller {int dummy; } ;
struct dw_spi {TYPE_1__* dma_ops; scalar_t__ dma_mapped; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_stop ) (struct dw_spi*) ;} ;

/* Variables and functions */
 struct dw_spi* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  spi_reset_chip (struct dw_spi*) ; 
 int /*<<< orphan*/  stub1 (struct dw_spi*) ; 

__attribute__((used)) static void dw_spi_handle_err(struct spi_controller *master,
		struct spi_message *msg)
{
	struct dw_spi *dws = spi_controller_get_devdata(master);

	if (dws->dma_mapped)
		dws->dma_ops->dma_stop(dws);

	spi_reset_chip(dws);
}