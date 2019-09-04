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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct pci_host_bridge {int dummy; } ;
struct mt7621_pcie {int /*<<< orphan*/  mem; int /*<<< orphan*/  ports; struct device* dev; } ;
struct TYPE_4__ {unsigned long end; scalar_t__ start; } ;
struct TYPE_3__ {unsigned long end; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_SYSRST_PCIE (int) ; 
 int /*<<< orphan*/  DEASSERT_SYSRST_PCIE (int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int MEMORY_BASE ; 
 int /*<<< orphan*/  RALINK_CLKCFG1 ; 
 int RALINK_PCIE0_CLK_EN ; 
 int RALINK_PCIE0_RST ; 
 int RALINK_PCIE1_CLK_EN ; 
 int RALINK_PCIE1_RST ; 
 int RALINK_PCIE2_CLK_EN ; 
 int RALINK_PCIE2_RST ; 
 int /*<<< orphan*/  RALINK_PCIE_CLK_GEN ; 
 int /*<<< orphan*/  RALINK_PCIE_CLK_GEN1 ; 
 int RALINK_PCIE_RST ; 
 scalar_t__ RALINK_PCI_BAR0SETUP_ADDR ; 
 scalar_t__ RALINK_PCI_CLASS ; 
 scalar_t__ RALINK_PCI_IMBASEBAR0_ADDR ; 
 scalar_t__ RALINK_PCI_IOBASE ; 
 int RALINK_PCI_IO_MAP_BASE ; 
 scalar_t__ RALINK_PCI_MEMBASE ; 
 scalar_t__ RALINK_PCI_PCICFG_ADDR ; 
 scalar_t__ RALINK_PCI_PCIMSK_ADDR ; 
 scalar_t__ RALINK_PCI_STATUS ; 
 int /*<<< orphan*/  RALINK_RSTCTRL ; 
 scalar_t__ RT6855_PCIE0_OFFSET ; 
 scalar_t__ RT6855_PCIE1_OFFSET ; 
 scalar_t__ RT6855_PCIE2_OFFSET ; 
 int /*<<< orphan*/  SYSC_REG_SYSTEM_CONFIG1 ; 
 int /*<<< orphan*/  bypass_pipe_rst (struct mt7621_pcie*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct pci_host_bridge* devm_pci_alloc_host_bridge (struct device*,int) ; 
 TYPE_2__ iomem_resource ; 
 TYPE_1__ ioport_resource ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mt7621_pci_parse_request_of_pci_ranges (struct mt7621_pcie*) ; 
 int mt7621_pcie_parse_dt (struct mt7621_pcie*) ; 
 int mt7621_pcie_register_host (struct pci_host_bridge*,int /*<<< orphan*/ *) ; 
 int mt7621_pcie_request_resources (struct mt7621_pcie*,int /*<<< orphan*/ *) ; 
 struct mt7621_pcie* pci_host_bridge_priv (struct pci_host_bridge*) ; 
 int pcie_link_status ; 
 int pcie_read (struct mt7621_pcie*,scalar_t__) ; 
 int /*<<< orphan*/  pcie_write (struct mt7621_pcie*,int,scalar_t__) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mt7621_pcie*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int read_config (struct mt7621_pcie*,int,int) ; 
 int /*<<< orphan*/  res ; 
 int /*<<< orphan*/  rt_sysc_m32 (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_phy_for_ssc (struct mt7621_pcie*) ; 
 int /*<<< orphan*/  setup_cm_memory_region (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_config (struct mt7621_pcie*,int,int,int) ; 

__attribute__((used)) static int mt7621_pci_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mt7621_pcie *pcie;
	struct pci_host_bridge *bridge;
	int err;
	u32 val = 0;
	LIST_HEAD(res);

	if (!dev->of_node)
		return -ENODEV;

	bridge = devm_pci_alloc_host_bridge(dev, sizeof(*pcie));
	if (!bridge)
		return -ENODEV;

	pcie = pci_host_bridge_priv(bridge);
	pcie->dev = dev;
	platform_set_drvdata(pdev, pcie);
	INIT_LIST_HEAD(&pcie->ports);

	err = mt7621_pcie_parse_dt(pcie);
	if (err) {
		dev_err(dev, "Parsing DT failed\n");
		return err;
	}

	/* set resources limits */
	iomem_resource.start = 0;
	iomem_resource.end = ~0UL; /* no limit */
	ioport_resource.start = 0;
	ioport_resource.end = ~0UL; /* no limit */

	val = RALINK_PCIE0_RST;
	val |= RALINK_PCIE1_RST;
	val |= RALINK_PCIE2_RST;

	ASSERT_SYSRST_PCIE(RALINK_PCIE0_RST | RALINK_PCIE1_RST | RALINK_PCIE2_RST);

	*(unsigned int *)(0xbe000060) &= ~(0x3<<10 | 0x3<<3);
	*(unsigned int *)(0xbe000060) |= 0x1<<10 | 0x1<<3;
	mdelay(100);
	*(unsigned int *)(0xbe000600) |= 0x1<<19 | 0x1<<8 | 0x1<<7; // use GPIO19/GPIO8/GPIO7 (PERST_N/UART_RXD3/UART_TXD3)
	mdelay(100);
	*(unsigned int *)(0xbe000620) &= ~(0x1<<19 | 0x1<<8 | 0x1<<7);		// clear DATA

	mdelay(100);

	val = RALINK_PCIE0_RST;
	val |= RALINK_PCIE1_RST;
	val |= RALINK_PCIE2_RST;

	DEASSERT_SYSRST_PCIE(val);

	if ((*(unsigned int *)(0xbe00000c)&0xFFFF) == 0x0101) // MT7621 E2
		bypass_pipe_rst(pcie);
	set_phy_for_ssc(pcie);

	val = read_config(pcie, 0, 0x70c);
	printk("Port 0 N_FTS = %x\n", (unsigned int)val);

	val = read_config(pcie, 1, 0x70c);
	printk("Port 1 N_FTS = %x\n", (unsigned int)val);

	val = read_config(pcie, 2, 0x70c);
	printk("Port 2 N_FTS = %x\n", (unsigned int)val);

	rt_sysc_m32(0, RALINK_PCIE_RST, RALINK_RSTCTRL);
	rt_sysc_m32(0x30, 2 << 4, SYSC_REG_SYSTEM_CONFIG1);

	rt_sysc_m32(0x80000000, 0, RALINK_PCIE_CLK_GEN);
	rt_sysc_m32(0x7f000000, 0xa << 24, RALINK_PCIE_CLK_GEN1);
	rt_sysc_m32(0, 0x80000000, RALINK_PCIE_CLK_GEN);

	mdelay(50);
	rt_sysc_m32(RALINK_PCIE_RST, 0, RALINK_RSTCTRL);

	/* Use GPIO control instead of PERST_N */
	*(unsigned int *)(0xbe000620) |= 0x1<<19 | 0x1<<8 | 0x1<<7;		// set DATA
	mdelay(1000);

	if ((pcie_read(pcie, RT6855_PCIE0_OFFSET + RALINK_PCI_STATUS) & 0x1) == 0) {
		printk("PCIE0 no card, disable it(RST&CLK)\n");
		ASSERT_SYSRST_PCIE(RALINK_PCIE0_RST);
		rt_sysc_m32(RALINK_PCIE0_CLK_EN, 0, RALINK_CLKCFG1);
		pcie_link_status &= ~(1<<0);
	} else {
		pcie_link_status |= 1<<0;
		val = pcie_read(pcie, RALINK_PCI_PCIMSK_ADDR);
		val |= (1<<20); // enable pcie1 interrupt
		pcie_write(pcie, val, RALINK_PCI_PCIMSK_ADDR);
	}

	if ((pcie_read(pcie, RT6855_PCIE1_OFFSET + RALINK_PCI_STATUS) & 0x1) == 0) {
		printk("PCIE1 no card, disable it(RST&CLK)\n");
		ASSERT_SYSRST_PCIE(RALINK_PCIE1_RST);
		rt_sysc_m32(RALINK_PCIE1_CLK_EN, 0, RALINK_CLKCFG1);
		pcie_link_status &= ~(1<<1);
	} else {
		pcie_link_status |= 1<<1;
		val = pcie_read(pcie, RALINK_PCI_PCIMSK_ADDR);
		val |= (1<<21); // enable pcie1 interrupt
		pcie_write(pcie, val, RALINK_PCI_PCIMSK_ADDR);
	}

	if ((pcie_read(pcie, RT6855_PCIE2_OFFSET + RALINK_PCI_STATUS) & 0x1) == 0) {
		printk("PCIE2 no card, disable it(RST&CLK)\n");
		ASSERT_SYSRST_PCIE(RALINK_PCIE2_RST);
		rt_sysc_m32(RALINK_PCIE2_CLK_EN, 0, RALINK_CLKCFG1);
		pcie_link_status &= ~(1<<2);
	} else {
		pcie_link_status |= 1<<2;
		val = pcie_read(pcie, RALINK_PCI_PCIMSK_ADDR);
		val |= (1<<22); // enable pcie2 interrupt
		pcie_write(pcie, val, RALINK_PCI_PCIMSK_ADDR);
	}

	if (pcie_link_status == 0)
		return 0;

/*
pcie(2/1/0) link status	pcie2_num	pcie1_num	pcie0_num
3'b000			x		x		x
3'b001			x		x		0
3'b010			x		0		x
3'b011			x		1		0
3'b100			0		x		x
3'b101			1		x		0
3'b110			1		0		x
3'b111			2		1		0
*/
	switch (pcie_link_status) {
	case 2:
		val = pcie_read(pcie, RALINK_PCI_PCICFG_ADDR);
		val &= ~0x00ff0000;
		val |= 0x1 << 16;	// port 0
		val |= 0x0 << 20;	// port 1
		pcie_write(pcie, val, RALINK_PCI_PCICFG_ADDR);
		break;
	case 4:
		val = pcie_read(pcie, RALINK_PCI_PCICFG_ADDR);
		val &= ~0x0fff0000;
		val |= 0x1 << 16;	//port0
		val |= 0x2 << 20;	//port1
		val |= 0x0 << 24;	//port2
		pcie_write(pcie, val, RALINK_PCI_PCICFG_ADDR);
		break;
	case 5:
		val = pcie_read(pcie, RALINK_PCI_PCICFG_ADDR);
		val &= ~0x0fff0000;
		val |= 0x0 << 16;	//port0
		val |= 0x2 << 20;	//port1
		val |= 0x1 << 24;	//port2
		pcie_write(pcie, val, RALINK_PCI_PCICFG_ADDR);
		break;
	case 6:
		val = pcie_read(pcie, RALINK_PCI_PCICFG_ADDR);
		val &= ~0x0fff0000;
		val |= 0x2 << 16;	//port0
		val |= 0x0 << 20;	//port1
		val |= 0x1 << 24;	//port2
		pcie_write(pcie, val, RALINK_PCI_PCICFG_ADDR);
		break;
	}

/*
	ioport_resource.start = mt7621_res_pci_io1.start;
	ioport_resource.end = mt7621_res_pci_io1.end;
*/

	pcie_write(pcie, 0xffffffff, RALINK_PCI_MEMBASE);
	pcie_write(pcie, RALINK_PCI_IO_MAP_BASE, RALINK_PCI_IOBASE);

	//PCIe0
	if ((pcie_link_status & 0x1) != 0) {
		/* open 7FFF:2G; ENABLE */
		pcie_write(pcie, 0x7FFF0001,
			   RT6855_PCIE0_OFFSET + RALINK_PCI_BAR0SETUP_ADDR);
		pcie_write(pcie, MEMORY_BASE,
			   RT6855_PCIE0_OFFSET + RALINK_PCI_IMBASEBAR0_ADDR);
		pcie_write(pcie, 0x06040001,
			   RT6855_PCIE0_OFFSET + RALINK_PCI_CLASS);
		printk("PCIE0 enabled\n");
	}

	//PCIe1
	if ((pcie_link_status & 0x2) != 0) {
		/* open 7FFF:2G; ENABLE */
		pcie_write(pcie, 0x7FFF0001,
			   RT6855_PCIE1_OFFSET + RALINK_PCI_BAR0SETUP_ADDR);
		pcie_write(pcie, MEMORY_BASE,
			   RT6855_PCIE1_OFFSET + RALINK_PCI_IMBASEBAR0_ADDR);
		pcie_write(pcie, 0x06040001,
			   RT6855_PCIE1_OFFSET + RALINK_PCI_CLASS);
		printk("PCIE1 enabled\n");
	}

	//PCIe2
	if ((pcie_link_status & 0x4) != 0) {
		/* open 7FFF:2G; ENABLE */
		pcie_write(pcie, 0x7FFF0001,
			   RT6855_PCIE2_OFFSET + RALINK_PCI_BAR0SETUP_ADDR);
		pcie_write(pcie, MEMORY_BASE,
			   RT6855_PCIE2_OFFSET + RALINK_PCI_IMBASEBAR0_ADDR);
		pcie_write(pcie, 0x06040001,
			   RT6855_PCIE2_OFFSET + RALINK_PCI_CLASS);
		printk("PCIE2 enabled\n");
	}

	switch (pcie_link_status) {
	case 7:
		val = read_config(pcie, 2, 0x4);
		write_config(pcie, 2, 0x4, val|0x4);
		val = read_config(pcie, 2, 0x70c);
		val &= ~(0xff)<<8;
		val |= 0x50<<8;
		write_config(pcie, 2, 0x70c, val);
	case 3:
	case 5:
	case 6:
		val = read_config(pcie, 1, 0x4);
		write_config(pcie, 1, 0x4, val|0x4);
		val = read_config(pcie, 1, 0x70c);
		val &= ~(0xff)<<8;
		val |= 0x50<<8;
		write_config(pcie, 1, 0x70c, val);
	default:
		val = read_config(pcie, 0, 0x4);
		write_config(pcie, 0, 0x4, val|0x4); //bus master enable
		val = read_config(pcie, 0, 0x70c);
		val &= ~(0xff)<<8;
		val |= 0x50<<8;
		write_config(pcie, 0, 0x70c, val);
	}

	err = mt7621_pci_parse_request_of_pci_ranges(pcie);
	if (err) {
		dev_err(dev, "Error requesting pci resources from ranges");
		return err;
	}

	setup_cm_memory_region(&pcie->mem);

	err = mt7621_pcie_request_resources(pcie, &res);
	if (err) {
		dev_err(dev, "Error requesting resources\n");
		return err;
	}

	err = mt7621_pcie_register_host(bridge, &res);
	if (err) {
		dev_err(dev, "Error registering host\n");
		return err;
	}

	return 0;
}