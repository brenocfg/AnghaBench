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
struct sst_dma {scalar_t__ chip; scalar_t__ ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  dw_remove (scalar_t__) ; 

__attribute__((used)) static void sst_dma_free(struct sst_dma *dma)
{

	if (dma == NULL)
		return;

	if (dma->ch)
		dma_release_channel(dma->ch);

	if (dma->chip)
		dw_remove(dma->chip);

}