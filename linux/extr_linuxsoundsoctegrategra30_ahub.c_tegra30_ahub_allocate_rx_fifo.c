#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra30_ahub_cif_conf {int audio_channels; int client_channels; scalar_t__ mono_conv; scalar_t__ truncate; int /*<<< orphan*/  direction; scalar_t__ replicate; scalar_t__ stereo_conv; scalar_t__ expand; void* client_bits; void* audio_bits; scalar_t__ threshold; } ;
typedef  enum tegra30_ahub_rxcif { ____Placeholder_tegra30_ahub_rxcif } tegra30_ahub_rxcif ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap_apbif; TYPE_1__* soc_data; scalar_t__ apbif_addr; int /*<<< orphan*/  rx_usage; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_audio_cif ) (int /*<<< orphan*/ ,int,struct tegra30_ahub_cif_conf*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int TEGRA30_AHUB_CHANNEL_CTRL ; 
 int TEGRA30_AHUB_CHANNEL_CTRL_COUNT ; 
 int TEGRA30_AHUB_CHANNEL_CTRL_RX_PACK_16 ; 
 int TEGRA30_AHUB_CHANNEL_CTRL_RX_PACK_EN ; 
 int TEGRA30_AHUB_CHANNEL_CTRL_RX_PACK_MASK ; 
 int TEGRA30_AHUB_CHANNEL_CTRL_RX_THRESHOLD_MASK ; 
 int TEGRA30_AHUB_CHANNEL_CTRL_RX_THRESHOLD_SHIFT ; 
 int TEGRA30_AHUB_CHANNEL_CTRL_STRIDE ; 
 scalar_t__ TEGRA30_AHUB_CHANNEL_RXFIFO ; 
 int TEGRA30_AHUB_CHANNEL_RXFIFO_STRIDE ; 
 int TEGRA30_AHUB_CIF_RX_CTRL ; 
 int TEGRA30_AHUB_CIF_RX_CTRL_STRIDE ; 
 int TEGRA30_AHUB_RXCIF_APBIF_RX0 ; 
 void* TEGRA30_AUDIOCIF_BITS_16 ; 
 int /*<<< orphan*/  TEGRA30_AUDIOCIF_DIRECTION_RX ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* ahub ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,struct tegra30_ahub_cif_conf*) ; 
 int tegra30_apbif_read (int) ; 
 int /*<<< orphan*/  tegra30_apbif_write (int,int) ; 

int tegra30_ahub_allocate_rx_fifo(enum tegra30_ahub_rxcif *rxcif,
				  char *dmachan, int dmachan_len,
				  dma_addr_t *fiforeg)
{
	int channel;
	u32 reg, val;
	struct tegra30_ahub_cif_conf cif_conf;

	channel = find_first_zero_bit(ahub->rx_usage,
				      TEGRA30_AHUB_CHANNEL_CTRL_COUNT);
	if (channel >= TEGRA30_AHUB_CHANNEL_CTRL_COUNT)
		return -EBUSY;

	__set_bit(channel, ahub->rx_usage);

	*rxcif = TEGRA30_AHUB_RXCIF_APBIF_RX0 + channel;
	snprintf(dmachan, dmachan_len, "rx%d", channel);
	*fiforeg = ahub->apbif_addr + TEGRA30_AHUB_CHANNEL_RXFIFO +
		   (channel * TEGRA30_AHUB_CHANNEL_RXFIFO_STRIDE);

	pm_runtime_get_sync(ahub->dev);

	reg = TEGRA30_AHUB_CHANNEL_CTRL +
	      (channel * TEGRA30_AHUB_CHANNEL_CTRL_STRIDE);
	val = tegra30_apbif_read(reg);
	val &= ~(TEGRA30_AHUB_CHANNEL_CTRL_RX_THRESHOLD_MASK |
		 TEGRA30_AHUB_CHANNEL_CTRL_RX_PACK_MASK);
	val |= (7 << TEGRA30_AHUB_CHANNEL_CTRL_RX_THRESHOLD_SHIFT) |
	       TEGRA30_AHUB_CHANNEL_CTRL_RX_PACK_EN |
	       TEGRA30_AHUB_CHANNEL_CTRL_RX_PACK_16;
	tegra30_apbif_write(reg, val);

	cif_conf.threshold = 0;
	cif_conf.audio_channels = 2;
	cif_conf.client_channels = 2;
	cif_conf.audio_bits = TEGRA30_AUDIOCIF_BITS_16;
	cif_conf.client_bits = TEGRA30_AUDIOCIF_BITS_16;
	cif_conf.expand = 0;
	cif_conf.stereo_conv = 0;
	cif_conf.replicate = 0;
	cif_conf.direction = TEGRA30_AUDIOCIF_DIRECTION_RX;
	cif_conf.truncate = 0;
	cif_conf.mono_conv = 0;

	reg = TEGRA30_AHUB_CIF_RX_CTRL +
	      (channel * TEGRA30_AHUB_CIF_RX_CTRL_STRIDE);
	ahub->soc_data->set_audio_cif(ahub->regmap_apbif, reg, &cif_conf);

	pm_runtime_put(ahub->dev);

	return 0;
}