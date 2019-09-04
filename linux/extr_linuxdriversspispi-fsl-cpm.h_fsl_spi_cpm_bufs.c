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
struct spi_transfer {int dummy; } ;
struct mpc8xxx_spi {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int fsl_spi_cpm_bufs(struct mpc8xxx_spi *mspi,
				   struct spi_transfer *t,
				   bool is_dma_mapped) { return 0; }