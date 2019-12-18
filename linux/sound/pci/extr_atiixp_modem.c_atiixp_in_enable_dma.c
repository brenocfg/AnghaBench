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
struct atiixp_modem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_REG_CMD_MODEM_IN_DMA_EN ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  atiixp_update (struct atiixp_modem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atiixp_in_enable_dma(struct atiixp_modem *chip, int on)
{
	atiixp_update(chip, CMD, ATI_REG_CMD_MODEM_IN_DMA_EN,
		      on ? ATI_REG_CMD_MODEM_IN_DMA_EN : 0);
}