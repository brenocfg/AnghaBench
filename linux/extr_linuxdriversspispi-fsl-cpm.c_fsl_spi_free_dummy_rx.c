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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * fsl_dummy_rx ; 
 int /*<<< orphan*/  fsl_dummy_rx_lock ; 
 int fsl_dummy_rx_refcnt ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fsl_spi_free_dummy_rx(void)
{
	mutex_lock(&fsl_dummy_rx_lock);

	switch (fsl_dummy_rx_refcnt) {
	case 0:
		WARN_ON(1);
		break;
	case 1:
		kfree(fsl_dummy_rx);
		fsl_dummy_rx = NULL;
		/* fall through */
	default:
		fsl_dummy_rx_refcnt--;
		break;
	}

	mutex_unlock(&fsl_dummy_rx_lock);
}