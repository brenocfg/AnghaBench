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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SPI_MRBLR ; 
 void* fsl_dummy_rx ; 
 int /*<<< orphan*/  fsl_dummy_rx_lock ; 
 int /*<<< orphan*/  fsl_dummy_rx_refcnt ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *fsl_spi_alloc_dummy_rx(void)
{
	mutex_lock(&fsl_dummy_rx_lock);

	if (!fsl_dummy_rx)
		fsl_dummy_rx = kmalloc(SPI_MRBLR, GFP_KERNEL);
	if (fsl_dummy_rx)
		fsl_dummy_rx_refcnt++;

	mutex_unlock(&fsl_dummy_rx_lock);

	return fsl_dummy_rx;
}