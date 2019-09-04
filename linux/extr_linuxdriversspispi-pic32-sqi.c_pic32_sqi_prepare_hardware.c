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
struct spi_master {int dummy; } ;
struct pic32_sqi {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ PESQI_CLK_CTRL_REG ; 
 int /*<<< orphan*/  PESQI_CLK_EN ; 
 scalar_t__ PESQI_CONF_REG ; 
 int /*<<< orphan*/  PESQI_EN ; 
 int /*<<< orphan*/  pic32_setbits (scalar_t__,int /*<<< orphan*/ ) ; 
 struct pic32_sqi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int pic32_sqi_prepare_hardware(struct spi_master *master)
{
	struct pic32_sqi *sqi = spi_master_get_devdata(master);

	/* enable spi interface */
	pic32_setbits(sqi->regs + PESQI_CONF_REG, PESQI_EN);
	/* enable spi clk */
	pic32_setbits(sqi->regs + PESQI_CLK_CTRL_REG, PESQI_CLK_EN);

	return 0;
}