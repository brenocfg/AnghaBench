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
struct TYPE_2__ {int index; } ;
struct azx_dev {TYPE_1__ core; } ;
struct azx {int dummy; } ;

/* Variables and functions */
 scalar_t__ AZX_REG_VS_SDXDPIB_XBASE ; 
 int AZX_REG_VS_SDXDPIB_XINTERVAL ; 
 unsigned int _snd_hdac_chip_readl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  azx_bus (struct azx*) ; 

__attribute__((used)) static unsigned int azx_skl_get_dpib_pos(struct azx *chip,
					 struct azx_dev *azx_dev)
{
	return _snd_hdac_chip_readl(azx_bus(chip),
				    AZX_REG_VS_SDXDPIB_XBASE +
				    (AZX_REG_VS_SDXDPIB_XINTERVAL *
				     azx_dev->core.index));
}