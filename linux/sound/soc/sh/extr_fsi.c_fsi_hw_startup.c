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
typedef  int u32 ;
struct fsi_stream {int sample_width; int /*<<< orphan*/  bus_option; } ;
struct fsi_priv {scalar_t__ lr_clk_inv; scalar_t__ bit_clk_inv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BUSOP_GET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CKG1 ; 
 int /*<<< orphan*/  CKG2 ; 
 int DIMD ; 
 int DMMD ; 
 int DOMD ; 
 int /*<<< orphan*/  OUT_SEL ; 
 int fsi_clk_enable (struct device*,struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_fifo_init (struct fsi_priv*,struct fsi_stream*,struct device*) ; 
 int /*<<< orphan*/  fsi_format_bus_setup (struct fsi_priv*,struct fsi_stream*,int,struct device*) ; 
 int /*<<< orphan*/  fsi_irq_clear_status (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_irq_disable (struct fsi_priv*,struct fsi_stream*) ; 
 scalar_t__ fsi_is_clk_master (struct fsi_priv*) ; 
 scalar_t__ fsi_is_spdif (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_reg_mask_set (struct fsi_priv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fsi_reg_write (struct fsi_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsi_spdif_clk_ctrl (struct fsi_priv*,int) ; 

__attribute__((used)) static int fsi_hw_startup(struct fsi_priv *fsi,
			  struct fsi_stream *io,
			  struct device *dev)
{
	u32 data = 0;

	/* clock setting */
	if (fsi_is_clk_master(fsi))
		data = DIMD | DOMD;

	fsi_reg_mask_set(fsi, CKG1, (DIMD | DOMD), data);

	/* clock inversion (CKG2) */
	data = 0;
	if (fsi->bit_clk_inv)
		data |= (1 << 0);
	if (fsi->lr_clk_inv)
		data |= (1 << 4);
	if (fsi_is_clk_master(fsi))
		data <<= 8;
	fsi_reg_write(fsi, CKG2, data);

	/* spdif ? */
	if (fsi_is_spdif(fsi)) {
		fsi_spdif_clk_ctrl(fsi, 1);
		fsi_reg_mask_set(fsi, OUT_SEL, DMMD, DMMD);
	}

	/*
	 * get bus settings
	 */
	data = 0;
	switch (io->sample_width) {
	case 2:
		data = BUSOP_GET(16, io->bus_option);
		break;
	case 4:
		data = BUSOP_GET(24, io->bus_option);
		break;
	}
	fsi_format_bus_setup(fsi, io, data, dev);

	/* irq clear */
	fsi_irq_disable(fsi, io);
	fsi_irq_clear_status(fsi);

	/* fifo init */
	fsi_fifo_init(fsi, io, dev);

	/* start master clock */
	if (fsi_is_clk_master(fsi))
		return fsi_clk_enable(dev, fsi);

	return 0;
}