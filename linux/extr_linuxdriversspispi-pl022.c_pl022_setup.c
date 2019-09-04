#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct ssp_clock_params {int cpsdvsr; unsigned int scr; } ;
struct TYPE_10__ {struct device_node* of_node; } ;
struct spi_device {unsigned int bits_per_word; size_t chip_select; int mode; TYPE_4__ dev; int /*<<< orphan*/  max_speed_hz; struct pl022_config_chip* controller_data; int /*<<< orphan*/  master; } ;
struct TYPE_9__ {scalar_t__ cpsdvsr; scalar_t__ scr; } ;
struct pl022_config_chip {unsigned int hierarchy; scalar_t__ iface; scalar_t__ com_mode; scalar_t__ rx_lev_trig; scalar_t__ tx_lev_trig; scalar_t__ ctrl_len; scalar_t__ wait_state; scalar_t__ duplex; unsigned int clkdelay; unsigned int slave_tx_disable; scalar_t__ cs_control; TYPE_3__ clk_freq; } ;
struct pl022 {scalar_t__ rx_lev_trig; scalar_t__ tx_lev_trig; TYPE_2__* vendor; TYPE_1__* master_info; int /*<<< orphan*/ * chipselects; } ;
struct device_node {int dummy; } ;
struct chip_data {scalar_t__ xfer_type; int n_bytes; int cpsr; int enable_dma; scalar_t__ cr1; scalar_t__ cr0; scalar_t__ dmacr; int /*<<< orphan*/  write; int /*<<< orphan*/  read; scalar_t__ cs_control; } ;
typedef  int /*<<< orphan*/  clk_freq ;
struct TYPE_8__ {unsigned int max_bpw; scalar_t__ loopback; scalar_t__ pl023; scalar_t__ extended_cr; } ;
struct TYPE_7__ {scalar_t__ enable_dma; } ;

/* Variables and functions */
 int CPSDVR_MAX ; 
 int CPSDVR_MIN ; 
 scalar_t__ DMA_TRANSFER ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int LOOPBACK_DISABLED ; 
 unsigned int LOOPBACK_ENABLED ; 
 int /*<<< orphan*/  READING_U16 ; 
 int /*<<< orphan*/  READING_U32 ; 
 int /*<<< orphan*/  READING_U8 ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LOOP ; 
 int SPI_LSB_FIRST ; 
 unsigned int SSP_CLK_FIRST_EDGE ; 
 unsigned int SSP_CLK_POL_IDLE_HIGH ; 
 unsigned int SSP_CLK_POL_IDLE_LOW ; 
 unsigned int SSP_CLK_SECOND_EDGE ; 
 int /*<<< orphan*/  SSP_CR0_MASK_CSS_ST ; 
 int /*<<< orphan*/  SSP_CR0_MASK_DSS ; 
 int /*<<< orphan*/  SSP_CR0_MASK_DSS_ST ; 
 int /*<<< orphan*/  SSP_CR0_MASK_FRF ; 
 int /*<<< orphan*/  SSP_CR0_MASK_FRF_ST ; 
 int /*<<< orphan*/  SSP_CR0_MASK_HALFDUP_ST ; 
 int /*<<< orphan*/  SSP_CR0_MASK_SCR ; 
 int /*<<< orphan*/  SSP_CR0_MASK_SPH ; 
 int /*<<< orphan*/  SSP_CR0_MASK_SPO ; 
 int /*<<< orphan*/  SSP_CR1_MASK_FBCLKDEL_ST ; 
 int /*<<< orphan*/  SSP_CR1_MASK_LBM ; 
 int /*<<< orphan*/  SSP_CR1_MASK_MS ; 
 int /*<<< orphan*/  SSP_CR1_MASK_MWAIT_ST ; 
 int /*<<< orphan*/  SSP_CR1_MASK_RENDN_ST ; 
 int /*<<< orphan*/  SSP_CR1_MASK_RXIFLSEL_ST ; 
 int /*<<< orphan*/  SSP_CR1_MASK_SOD ; 
 int /*<<< orphan*/  SSP_CR1_MASK_SSE ; 
 int /*<<< orphan*/  SSP_CR1_MASK_TENDN_ST ; 
 int /*<<< orphan*/  SSP_CR1_MASK_TXIFLSEL_ST ; 
 unsigned int SSP_DISABLED ; 
 int /*<<< orphan*/  SSP_DMACR_MASK_RXDMAE ; 
 int /*<<< orphan*/  SSP_DMACR_MASK_TXDMAE ; 
 unsigned int SSP_DMA_DISABLED ; 
 unsigned int SSP_DMA_ENABLED ; 
 unsigned int SSP_MASTER ; 
 unsigned int SSP_RX_LSB ; 
 unsigned int SSP_RX_MSB ; 
 unsigned int SSP_TX_LSB ; 
 unsigned int SSP_TX_MSB ; 
 int /*<<< orphan*/  SSP_WRITE_BITS (scalar_t__,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITING_U16 ; 
 int /*<<< orphan*/  WRITING_U32 ; 
 int /*<<< orphan*/  WRITING_U8 ; 
 int calculate_effective_freq (struct pl022*,int /*<<< orphan*/ ,struct ssp_clock_params*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct chip_data*) ; 
 struct chip_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ssp_clock_params*,TYPE_3__*,int) ; 
 scalar_t__ null_cs_control ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 struct pl022_config_chip pl022_default_chip_info ; 
 struct chip_data* spi_get_ctldata (struct spi_device*) ; 
 struct pl022* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_set_ctldata (struct spi_device*,struct chip_data*) ; 
 int verify_controller_parameters (struct pl022*,struct pl022_config_chip const*) ; 

__attribute__((used)) static int pl022_setup(struct spi_device *spi)
{
	struct pl022_config_chip const *chip_info;
	struct pl022_config_chip chip_info_dt;
	struct chip_data *chip;
	struct ssp_clock_params clk_freq = { .cpsdvsr = 0, .scr = 0};
	int status = 0;
	struct pl022 *pl022 = spi_master_get_devdata(spi->master);
	unsigned int bits = spi->bits_per_word;
	u32 tmp;
	struct device_node *np = spi->dev.of_node;

	if (!spi->max_speed_hz)
		return -EINVAL;

	/* Get controller_state if one is supplied */
	chip = spi_get_ctldata(spi);

	if (chip == NULL) {
		chip = kzalloc(sizeof(struct chip_data), GFP_KERNEL);
		if (!chip)
			return -ENOMEM;
		dev_dbg(&spi->dev,
			"allocated memory for controller's runtime state\n");
	}

	/* Get controller data if one is supplied */
	chip_info = spi->controller_data;

	if (chip_info == NULL) {
		if (np) {
			chip_info_dt = pl022_default_chip_info;

			chip_info_dt.hierarchy = SSP_MASTER;
			of_property_read_u32(np, "pl022,interface",
				&chip_info_dt.iface);
			of_property_read_u32(np, "pl022,com-mode",
				&chip_info_dt.com_mode);
			of_property_read_u32(np, "pl022,rx-level-trig",
				&chip_info_dt.rx_lev_trig);
			of_property_read_u32(np, "pl022,tx-level-trig",
				&chip_info_dt.tx_lev_trig);
			of_property_read_u32(np, "pl022,ctrl-len",
				&chip_info_dt.ctrl_len);
			of_property_read_u32(np, "pl022,wait-state",
				&chip_info_dt.wait_state);
			of_property_read_u32(np, "pl022,duplex",
				&chip_info_dt.duplex);

			chip_info = &chip_info_dt;
		} else {
			chip_info = &pl022_default_chip_info;
			/* spi_board_info.controller_data not is supplied */
			dev_dbg(&spi->dev,
				"using default controller_data settings\n");
		}
	} else
		dev_dbg(&spi->dev,
			"using user supplied controller_data settings\n");

	/*
	 * We can override with custom divisors, else we use the board
	 * frequency setting
	 */
	if ((0 == chip_info->clk_freq.cpsdvsr)
	    && (0 == chip_info->clk_freq.scr)) {
		status = calculate_effective_freq(pl022,
						  spi->max_speed_hz,
						  &clk_freq);
		if (status < 0)
			goto err_config_params;
	} else {
		memcpy(&clk_freq, &chip_info->clk_freq, sizeof(clk_freq));
		if ((clk_freq.cpsdvsr % 2) != 0)
			clk_freq.cpsdvsr =
				clk_freq.cpsdvsr - 1;
	}
	if ((clk_freq.cpsdvsr < CPSDVR_MIN)
	    || (clk_freq.cpsdvsr > CPSDVR_MAX)) {
		status = -EINVAL;
		dev_err(&spi->dev,
			"cpsdvsr is configured incorrectly\n");
		goto err_config_params;
	}

	status = verify_controller_parameters(pl022, chip_info);
	if (status) {
		dev_err(&spi->dev, "controller data is incorrect");
		goto err_config_params;
	}

	pl022->rx_lev_trig = chip_info->rx_lev_trig;
	pl022->tx_lev_trig = chip_info->tx_lev_trig;

	/* Now set controller state based on controller data */
	chip->xfer_type = chip_info->com_mode;
	if (!chip_info->cs_control) {
		chip->cs_control = null_cs_control;
		if (!gpio_is_valid(pl022->chipselects[spi->chip_select]))
			dev_warn(&spi->dev,
				 "invalid chip select\n");
	} else
		chip->cs_control = chip_info->cs_control;

	/* Check bits per word with vendor specific range */
	if ((bits <= 3) || (bits > pl022->vendor->max_bpw)) {
		status = -ENOTSUPP;
		dev_err(&spi->dev, "illegal data size for this controller!\n");
		dev_err(&spi->dev, "This controller can only handle 4 <= n <= %d bit words\n",
				pl022->vendor->max_bpw);
		goto err_config_params;
	} else if (bits <= 8) {
		dev_dbg(&spi->dev, "4 <= n <=8 bits per word\n");
		chip->n_bytes = 1;
		chip->read = READING_U8;
		chip->write = WRITING_U8;
	} else if (bits <= 16) {
		dev_dbg(&spi->dev, "9 <= n <= 16 bits per word\n");
		chip->n_bytes = 2;
		chip->read = READING_U16;
		chip->write = WRITING_U16;
	} else {
		dev_dbg(&spi->dev, "17 <= n <= 32 bits per word\n");
		chip->n_bytes = 4;
		chip->read = READING_U32;
		chip->write = WRITING_U32;
	}

	/* Now Initialize all register settings required for this chip */
	chip->cr0 = 0;
	chip->cr1 = 0;
	chip->dmacr = 0;
	chip->cpsr = 0;
	if ((chip_info->com_mode == DMA_TRANSFER)
	    && ((pl022->master_info)->enable_dma)) {
		chip->enable_dma = true;
		dev_dbg(&spi->dev, "DMA mode set in controller state\n");
		SSP_WRITE_BITS(chip->dmacr, SSP_DMA_ENABLED,
			       SSP_DMACR_MASK_RXDMAE, 0);
		SSP_WRITE_BITS(chip->dmacr, SSP_DMA_ENABLED,
			       SSP_DMACR_MASK_TXDMAE, 1);
	} else {
		chip->enable_dma = false;
		dev_dbg(&spi->dev, "DMA mode NOT set in controller state\n");
		SSP_WRITE_BITS(chip->dmacr, SSP_DMA_DISABLED,
			       SSP_DMACR_MASK_RXDMAE, 0);
		SSP_WRITE_BITS(chip->dmacr, SSP_DMA_DISABLED,
			       SSP_DMACR_MASK_TXDMAE, 1);
	}

	chip->cpsr = clk_freq.cpsdvsr;

	/* Special setup for the ST micro extended control registers */
	if (pl022->vendor->extended_cr) {
		u32 etx;

		if (pl022->vendor->pl023) {
			/* These bits are only in the PL023 */
			SSP_WRITE_BITS(chip->cr1, chip_info->clkdelay,
				       SSP_CR1_MASK_FBCLKDEL_ST, 13);
		} else {
			/* These bits are in the PL022 but not PL023 */
			SSP_WRITE_BITS(chip->cr0, chip_info->duplex,
				       SSP_CR0_MASK_HALFDUP_ST, 5);
			SSP_WRITE_BITS(chip->cr0, chip_info->ctrl_len,
				       SSP_CR0_MASK_CSS_ST, 16);
			SSP_WRITE_BITS(chip->cr0, chip_info->iface,
				       SSP_CR0_MASK_FRF_ST, 21);
			SSP_WRITE_BITS(chip->cr1, chip_info->wait_state,
				       SSP_CR1_MASK_MWAIT_ST, 6);
		}
		SSP_WRITE_BITS(chip->cr0, bits - 1,
			       SSP_CR0_MASK_DSS_ST, 0);

		if (spi->mode & SPI_LSB_FIRST) {
			tmp = SSP_RX_LSB;
			etx = SSP_TX_LSB;
		} else {
			tmp = SSP_RX_MSB;
			etx = SSP_TX_MSB;
		}
		SSP_WRITE_BITS(chip->cr1, tmp, SSP_CR1_MASK_RENDN_ST, 4);
		SSP_WRITE_BITS(chip->cr1, etx, SSP_CR1_MASK_TENDN_ST, 5);
		SSP_WRITE_BITS(chip->cr1, chip_info->rx_lev_trig,
			       SSP_CR1_MASK_RXIFLSEL_ST, 7);
		SSP_WRITE_BITS(chip->cr1, chip_info->tx_lev_trig,
			       SSP_CR1_MASK_TXIFLSEL_ST, 10);
	} else {
		SSP_WRITE_BITS(chip->cr0, bits - 1,
			       SSP_CR0_MASK_DSS, 0);
		SSP_WRITE_BITS(chip->cr0, chip_info->iface,
			       SSP_CR0_MASK_FRF, 4);
	}

	/* Stuff that is common for all versions */
	if (spi->mode & SPI_CPOL)
		tmp = SSP_CLK_POL_IDLE_HIGH;
	else
		tmp = SSP_CLK_POL_IDLE_LOW;
	SSP_WRITE_BITS(chip->cr0, tmp, SSP_CR0_MASK_SPO, 6);

	if (spi->mode & SPI_CPHA)
		tmp = SSP_CLK_SECOND_EDGE;
	else
		tmp = SSP_CLK_FIRST_EDGE;
	SSP_WRITE_BITS(chip->cr0, tmp, SSP_CR0_MASK_SPH, 7);

	SSP_WRITE_BITS(chip->cr0, clk_freq.scr, SSP_CR0_MASK_SCR, 8);
	/* Loopback is available on all versions except PL023 */
	if (pl022->vendor->loopback) {
		if (spi->mode & SPI_LOOP)
			tmp = LOOPBACK_ENABLED;
		else
			tmp = LOOPBACK_DISABLED;
		SSP_WRITE_BITS(chip->cr1, tmp, SSP_CR1_MASK_LBM, 0);
	}
	SSP_WRITE_BITS(chip->cr1, SSP_DISABLED, SSP_CR1_MASK_SSE, 1);
	SSP_WRITE_BITS(chip->cr1, chip_info->hierarchy, SSP_CR1_MASK_MS, 2);
	SSP_WRITE_BITS(chip->cr1, chip_info->slave_tx_disable, SSP_CR1_MASK_SOD,
		3);

	/* Save controller_state */
	spi_set_ctldata(spi, chip);
	return status;
 err_config_params:
	spi_set_ctldata(spi, NULL);
	kfree(chip);
	return status;
}