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
typedef  int u8 ;
typedef  int u32 ;
struct pci_device_id {int /*<<< orphan*/  device; int /*<<< orphan*/  driver_data; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct ath_softc* priv; } ;
struct ath_softc {int /*<<< orphan*/  irq; scalar_t__ mem; TYPE_1__* sc_ah; int /*<<< orphan*/  driver_data; int /*<<< orphan*/ * dev; struct ieee80211_hw* hw; } ;
typedef  int /*<<< orphan*/  hw_name ;
struct TYPE_2__ {int msi_enabled; scalar_t__ msi_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int L1_CACHE_BYTES ; 
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_fill_chanctx_ops () ; 
 int /*<<< orphan*/  ath9k_hw_name (TYPE_1__*,char*,int) ; 
 int ath9k_init_device (int /*<<< orphan*/ ,struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_ops ; 
 scalar_t__ ath9k_use_msi ; 
 int /*<<< orphan*/  ath_isr ; 
 int /*<<< orphan*/  ath_pci_bus_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ath_softc*) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 scalar_t__ pci_enable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int,int*) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int,int) ; 
 scalar_t__ pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__* pcim_iomap_table (struct pci_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ath_softc*) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*,char*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct ath_softc *sc;
	struct ieee80211_hw *hw;
	u8 csz;
	u32 val;
	int ret = 0;
	char hw_name[64];
	int msi_enabled = 0;

	if (pcim_enable_device(pdev))
		return -EIO;

	ret =  pci_set_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret) {
		pr_err("32-bit DMA not available\n");
		return ret;
	}

	ret = pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(32));
	if (ret) {
		pr_err("32-bit DMA consistent DMA enable failed\n");
		return ret;
	}

	/*
	 * Cache line size is used to size and align various
	 * structures used to communicate with the hardware.
	 */
	pci_read_config_byte(pdev, PCI_CACHE_LINE_SIZE, &csz);
	if (csz == 0) {
		/*
		 * Linux 2.4.18 (at least) writes the cache line size
		 * register as a 16-bit wide register which is wrong.
		 * We must have this setup properly for rx buffer
		 * DMA to work so force a reasonable value here if it
		 * comes up zero.
		 */
		csz = L1_CACHE_BYTES / sizeof(u32);
		pci_write_config_byte(pdev, PCI_CACHE_LINE_SIZE, csz);
	}
	/*
	 * The default setting of latency timer yields poor results,
	 * set it to the value used by other systems. It may be worth
	 * tweaking this setting more.
	 */
	pci_write_config_byte(pdev, PCI_LATENCY_TIMER, 0xa8);

	pci_set_master(pdev);

	/*
	 * Disable the RETRY_TIMEOUT register (0x41) to keep
	 * PCI Tx retries from interfering with C3 CPU state.
	 */
	pci_read_config_dword(pdev, 0x40, &val);
	if ((val & 0x0000ff00) != 0)
		pci_write_config_dword(pdev, 0x40, val & 0xffff00ff);

	ret = pcim_iomap_regions(pdev, BIT(0), "ath9k");
	if (ret) {
		dev_err(&pdev->dev, "PCI memory region reserve error\n");
		return -ENODEV;
	}

	ath9k_fill_chanctx_ops();
	hw = ieee80211_alloc_hw(sizeof(struct ath_softc), &ath9k_ops);
	if (!hw) {
		dev_err(&pdev->dev, "No memory for ieee80211_hw\n");
		return -ENOMEM;
	}

	SET_IEEE80211_DEV(hw, &pdev->dev);
	pci_set_drvdata(pdev, hw);

	sc = hw->priv;
	sc->hw = hw;
	sc->dev = &pdev->dev;
	sc->mem = pcim_iomap_table(pdev)[0];
	sc->driver_data = id->driver_data;

	if (ath9k_use_msi) {
		if (pci_enable_msi(pdev) == 0) {
			msi_enabled = 1;
			dev_err(&pdev->dev, "Using MSI\n");
		} else {
			dev_err(&pdev->dev, "Using INTx\n");
		}
	}

	if (!msi_enabled)
		ret = request_irq(pdev->irq, ath_isr, IRQF_SHARED, "ath9k", sc);
	else
		ret = request_irq(pdev->irq, ath_isr, 0, "ath9k", sc);

	if (ret) {
		dev_err(&pdev->dev, "request_irq failed\n");
		goto err_irq;
	}

	sc->irq = pdev->irq;

	ret = ath9k_init_device(id->device, sc, &ath_pci_bus_ops);
	if (ret) {
		dev_err(&pdev->dev, "Failed to initialize device\n");
		goto err_init;
	}

	sc->sc_ah->msi_enabled = msi_enabled;
	sc->sc_ah->msi_reg = 0;

	ath9k_hw_name(sc->sc_ah, hw_name, sizeof(hw_name));
	wiphy_info(hw->wiphy, "%s mem=0x%lx, irq=%d\n",
		   hw_name, (unsigned long)sc->mem, pdev->irq);

	return 0;

err_init:
	free_irq(sc->irq, sc);
err_irq:
	ieee80211_free_hw(hw);
	return ret;
}