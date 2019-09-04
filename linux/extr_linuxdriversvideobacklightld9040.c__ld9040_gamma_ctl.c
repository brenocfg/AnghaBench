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
struct ld9040 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_ONLY ; 
 unsigned int GAMMA_TABLE_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ld9040_panel_send_sequence (struct ld9040*,int /*<<< orphan*/ ) ; 
 int ld9040_spi_write (struct ld9040*,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  seq_gamma_ctrl ; 
 int /*<<< orphan*/  seq_gamma_start ; 

__attribute__((used)) static int _ld9040_gamma_ctl(struct ld9040 *lcd, const unsigned int *gamma)
{
	unsigned int i = 0;
	int ret = 0;

	/* start gamma table updating. */
	ret = ld9040_panel_send_sequence(lcd, seq_gamma_start);
	if (ret) {
		dev_err(lcd->dev, "failed to disable gamma table updating.\n");
		goto gamma_err;
	}

	for (i = 0 ; i < GAMMA_TABLE_COUNT; i++) {
		ret = ld9040_spi_write(lcd, DATA_ONLY, gamma[i]);
		if (ret) {
			dev_err(lcd->dev, "failed to set gamma table.\n");
			goto gamma_err;
		}
	}

	/* update gamma table. */
	ret = ld9040_panel_send_sequence(lcd, seq_gamma_ctrl);
	if (ret)
		dev_err(lcd->dev, "failed to update gamma table.\n");

gamma_err:
	return ret;
}