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
struct s6e63m0 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DATA_ONLY ; 
 unsigned int GAMMA_TABLE_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int s6e63m0_spi_write (struct s6e63m0*,int,unsigned int const) ; 

__attribute__((used)) static int _s6e63m0_gamma_ctl(struct s6e63m0 *lcd, const unsigned int *gamma)
{
	unsigned int i = 0;
	int ret = 0;

	/* disable gamma table updating. */
	ret = s6e63m0_spi_write(lcd, 0xfa, 0x00);
	if (ret) {
		dev_err(lcd->dev, "failed to disable gamma table updating.\n");
		goto gamma_err;
	}

	for (i = 0 ; i < GAMMA_TABLE_COUNT; i++) {
		ret = s6e63m0_spi_write(lcd, DATA_ONLY, gamma[i]);
		if (ret) {
			dev_err(lcd->dev, "failed to set gamma table.\n");
			goto gamma_err;
		}
	}

	/* update gamma table. */
	ret = s6e63m0_spi_write(lcd, 0xfa, 0x01);
	if (ret)
		dev_err(lcd->dev, "failed to update gamma table.\n");

gamma_err:
	return ret;
}