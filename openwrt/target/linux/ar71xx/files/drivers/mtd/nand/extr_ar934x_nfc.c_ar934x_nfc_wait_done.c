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
struct ar934x_nfc {int dummy; } ;

/* Variables and functions */
 scalar_t__ ar934x_nfc_use_irq (struct ar934x_nfc*) ; 
 int ar934x_nfc_wait_dev_ready (struct ar934x_nfc*) ; 
 int ar934x_nfc_wait_dma_ready (struct ar934x_nfc*) ; 
 int ar934x_nfc_wait_irq (struct ar934x_nfc*) ; 

__attribute__((used)) static int
ar934x_nfc_wait_done(struct ar934x_nfc *nfc)
{
	int ret;

	if (ar934x_nfc_use_irq(nfc))
		ret = ar934x_nfc_wait_irq(nfc);
	else
		ret = ar934x_nfc_wait_dev_ready(nfc);

	if (ret)
		return ret;

	return ar934x_nfc_wait_dma_ready(nfc);
}