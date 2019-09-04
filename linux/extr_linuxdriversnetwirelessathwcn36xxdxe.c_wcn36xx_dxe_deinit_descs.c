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
struct wcn36xx_dxe_desc {int dummy; } ;
struct wcn36xx_dxe_ch {int desc_num; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  cpu_addr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wcn36xx_dxe_deinit_descs(struct device *dev, struct wcn36xx_dxe_ch *wcn_ch)
{
	size_t size;

	size = wcn_ch->desc_num * sizeof(struct wcn36xx_dxe_desc);
	dma_free_coherent(dev, size,wcn_ch->cpu_addr, wcn_ch->dma_addr);
}