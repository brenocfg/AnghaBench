#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct p54u_priv {TYPE_2__* udev; TYPE_1__* fw; } ;
struct p54p_csr {int /*<<< orphan*/  int_ack; int /*<<< orphan*/  int_ident; int /*<<< orphan*/  dev_int; int /*<<< orphan*/  int_enable; int /*<<< orphan*/  ctrl_stat; int /*<<< orphan*/  direct_mem_win; int /*<<< orphan*/  dma_ctrl; int /*<<< orphan*/  dma_len; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  direct_mem_base; } ;
struct ieee80211_hw {struct p54u_priv* priv; } ;
typedef  int __le32 ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {unsigned int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ISL38XX_CTRL_STAT_CLKRUN ; 
 int ISL38XX_CTRL_STAT_RAMBOOT ; 
 int ISL38XX_CTRL_STAT_RESET ; 
 unsigned int ISL38XX_DEV_FIRMWARE_ADDR ; 
 int ISL38XX_DEV_INT_RESET ; 
 int ISL38XX_DMA_MASTER_CONTROL_TRIGGER ; 
 int ISL38XX_DMA_STATUS_DONE ; 
 int ISL38XX_DMA_STATUS_READY ; 
 int ISL38XX_INT_IDENT_INIT ; 
 int NET2280_BASE ; 
 int NET2280_BASE2 ; 
 int /*<<< orphan*/  NET2280_BRG_CFG_U16 ; 
 int /*<<< orphan*/  NET2280_BRG_CFG_U32 ; 
 int /*<<< orphan*/  NET2280_BRG_U32 ; 
 int NET2280_CLEAR_NAK_OUT_PACKETS_MODE ; 
 int NET2280_CLK_30Mhz ; 
 scalar_t__ NET2280_DEVINIT ; 
 int /*<<< orphan*/  NET2280_DEV_CFG_U16 ; 
 int /*<<< orphan*/  NET2280_DEV_CFG_U32 ; 
 int /*<<< orphan*/  NET2280_DEV_U32 ; 
 int NET2280_EPA_FIFO_PCI_ADDR ; 
 scalar_t__ NET2280_EPA_RSP ; 
 scalar_t__ NET2280_EPA_STAT ; 
 scalar_t__ NET2280_EPC_RSP ; 
 int NET2280_FIFO_FLUSH ; 
 scalar_t__ NET2280_GPIOCTL ; 
 scalar_t__ NET2280_IRQSTAT1 ; 
 int NET2280_PCI_ENABLE ; 
 int NET2280_PCI_INTA_INTERRUPT ; 
 int NET2280_PCI_INTA_INTERRUPT_ENABLE ; 
 int NET2280_PCI_SOFT_RESET ; 
 scalar_t__ NET2280_RELNUM ; 
 scalar_t__ NET2280_USBIRQENB1 ; 
 int NET2280_USB_INTERRUPT_ENABLE ; 
 int P54U_BRG_POWER_DOWN ; 
 int P54U_BRG_POWER_UP ; 
 int P54U_DEV_BASE ; 
 int /*<<< orphan*/  P54U_PIPE_DATA ; 
 int /*<<< orphan*/  P54U_PIPE_INT ; 
 int PCI_BASE_ADDRESS_0 ; 
 scalar_t__ PCI_BASE_ADDRESS_2 ; 
 int PCI_COMMAND ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 scalar_t__ PCI_STATUS ; 
 int PCI_STATUS_REC_MASTER_ABORT ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int p54u_bulk_msg (struct p54u_priv*,int /*<<< orphan*/ ,void*,unsigned int) ; 
 int p54u_read (struct p54u_priv*,void*,int /*<<< orphan*/ ,int,int*) ; 
 int p54u_write (struct p54u_priv*,void*,int /*<<< orphan*/ ,int,int) ; 
 int usb_interrupt_msg (TYPE_2__*,int /*<<< orphan*/ ,void*,int,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p54u_upload_firmware_net2280(struct ieee80211_hw *dev)
{
	struct p54u_priv *priv = dev->priv;
	const struct p54p_csr *devreg = (const struct p54p_csr *) P54U_DEV_BASE;
	int err, alen;
	void *buf;
	__le32 reg;
	unsigned int remains, offset;
	const u8 *data;

	buf = kmalloc(512, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

#define P54U_WRITE(type, addr, data) \
	do {\
		err = p54u_write(priv, buf, type,\
				 cpu_to_le32((u32)(unsigned long)addr), data);\
		if (err) \
			goto fail;\
	} while (0)

#define P54U_READ(type, addr) \
	do {\
		err = p54u_read(priv, buf, type,\
				cpu_to_le32((u32)(unsigned long)addr), &reg);\
		if (err)\
			goto fail;\
	} while (0)

	/* power down net2280 bridge */
	P54U_READ(NET2280_BRG_U32, NET2280_GPIOCTL);
	reg |= cpu_to_le32(P54U_BRG_POWER_DOWN);
	reg &= cpu_to_le32(~P54U_BRG_POWER_UP);
	P54U_WRITE(NET2280_BRG_U32, NET2280_GPIOCTL, reg);

	mdelay(100);

	/* power up bridge */
	reg |= cpu_to_le32(P54U_BRG_POWER_UP);
	reg &= cpu_to_le32(~P54U_BRG_POWER_DOWN);
	P54U_WRITE(NET2280_BRG_U32, NET2280_GPIOCTL, reg);

	mdelay(100);

	P54U_WRITE(NET2280_BRG_U32, NET2280_DEVINIT,
		   cpu_to_le32(NET2280_CLK_30Mhz |
			       NET2280_PCI_ENABLE |
			       NET2280_PCI_SOFT_RESET));

	mdelay(20);

	P54U_WRITE(NET2280_BRG_CFG_U16, PCI_COMMAND,
		   cpu_to_le32(PCI_COMMAND_MEMORY |
			       PCI_COMMAND_MASTER));

	P54U_WRITE(NET2280_BRG_CFG_U32, PCI_BASE_ADDRESS_0,
		   cpu_to_le32(NET2280_BASE));

	P54U_READ(NET2280_BRG_CFG_U16, PCI_STATUS);
	reg |= cpu_to_le32(PCI_STATUS_REC_MASTER_ABORT);
	P54U_WRITE(NET2280_BRG_CFG_U16, PCI_STATUS, reg);

	// TODO: we really need this?
	P54U_READ(NET2280_BRG_U32, NET2280_RELNUM);

	P54U_WRITE(NET2280_BRG_U32, NET2280_EPA_RSP,
		   cpu_to_le32(NET2280_CLEAR_NAK_OUT_PACKETS_MODE));
	P54U_WRITE(NET2280_BRG_U32, NET2280_EPC_RSP,
		   cpu_to_le32(NET2280_CLEAR_NAK_OUT_PACKETS_MODE));

	P54U_WRITE(NET2280_BRG_CFG_U32, PCI_BASE_ADDRESS_2,
		   cpu_to_le32(NET2280_BASE2));

	/* finally done setting up the bridge */

	P54U_WRITE(NET2280_DEV_CFG_U16, 0x10000 | PCI_COMMAND,
		   cpu_to_le32(PCI_COMMAND_MEMORY |
			       PCI_COMMAND_MASTER));

	P54U_WRITE(NET2280_DEV_CFG_U16, 0x10000 | 0x40 /* TRDY timeout */, 0);
	P54U_WRITE(NET2280_DEV_CFG_U32, 0x10000 | PCI_BASE_ADDRESS_0,
		   cpu_to_le32(P54U_DEV_BASE));

	P54U_WRITE(NET2280_BRG_U32, NET2280_USBIRQENB1, 0);
	P54U_WRITE(NET2280_BRG_U32, NET2280_IRQSTAT1,
		   cpu_to_le32(NET2280_PCI_INTA_INTERRUPT));

	/* do romboot */
	P54U_WRITE(NET2280_DEV_U32, &devreg->int_enable, 0);

	P54U_READ(NET2280_DEV_U32, &devreg->ctrl_stat);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RAMBOOT);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_CLKRUN);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	mdelay(20);

	reg |= cpu_to_le32(ISL38XX_CTRL_STAT_RESET);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	mdelay(20);

	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	mdelay(100);

	P54U_READ(NET2280_DEV_U32, &devreg->int_ident);
	P54U_WRITE(NET2280_DEV_U32, &devreg->int_ack, reg);

	/* finally, we can upload firmware now! */
	remains = priv->fw->size;
	data = priv->fw->data;
	offset = ISL38XX_DEV_FIRMWARE_ADDR;

	while (remains) {
		unsigned int block_len = min(remains, (unsigned int)512);
		memcpy(buf, data, block_len);

		err = p54u_bulk_msg(priv, P54U_PIPE_DATA, buf, block_len);
		if (err) {
			dev_err(&priv->udev->dev, "(p54usb) firmware block "
						  "upload failed\n");
			goto fail;
		}

		P54U_WRITE(NET2280_DEV_U32, &devreg->direct_mem_base,
			   cpu_to_le32(0xc0000f00));

		P54U_WRITE(NET2280_DEV_U32,
			   0x0020 | (unsigned long)&devreg->direct_mem_win, 0);
		P54U_WRITE(NET2280_DEV_U32,
			   0x0020 | (unsigned long)&devreg->direct_mem_win,
			   cpu_to_le32(1));

		P54U_WRITE(NET2280_DEV_U32,
			   0x0024 | (unsigned long)&devreg->direct_mem_win,
			   cpu_to_le32(block_len));
		P54U_WRITE(NET2280_DEV_U32,
			   0x0028 | (unsigned long)&devreg->direct_mem_win,
			   cpu_to_le32(offset));

		P54U_WRITE(NET2280_DEV_U32, &devreg->dma_addr,
			   cpu_to_le32(NET2280_EPA_FIFO_PCI_ADDR));
		P54U_WRITE(NET2280_DEV_U32, &devreg->dma_len,
			   cpu_to_le32(block_len >> 2));
		P54U_WRITE(NET2280_DEV_U32, &devreg->dma_ctrl,
			   cpu_to_le32(ISL38XX_DMA_MASTER_CONTROL_TRIGGER));

		mdelay(10);

		P54U_READ(NET2280_DEV_U32,
			  0x002C | (unsigned long)&devreg->direct_mem_win);
		if (!(reg & cpu_to_le32(ISL38XX_DMA_STATUS_DONE)) ||
		    !(reg & cpu_to_le32(ISL38XX_DMA_STATUS_READY))) {
			dev_err(&priv->udev->dev, "(p54usb) firmware DMA "
						  "transfer failed\n");
			goto fail;
		}

		P54U_WRITE(NET2280_BRG_U32, NET2280_EPA_STAT,
			   cpu_to_le32(NET2280_FIFO_FLUSH));

		remains -= block_len;
		data += block_len;
		offset += block_len;
	}

	/* do ramboot */
	P54U_READ(NET2280_DEV_U32, &devreg->ctrl_stat);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_CLKRUN);
	reg |= cpu_to_le32(ISL38XX_CTRL_STAT_RAMBOOT);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	mdelay(20);

	reg |= cpu_to_le32(ISL38XX_CTRL_STAT_RESET);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	reg &= cpu_to_le32(~ISL38XX_CTRL_STAT_RESET);
	P54U_WRITE(NET2280_DEV_U32, &devreg->ctrl_stat, reg);

	mdelay(100);

	P54U_READ(NET2280_DEV_U32, &devreg->int_ident);
	P54U_WRITE(NET2280_DEV_U32, &devreg->int_ack, reg);

	/* start up the firmware */
	P54U_WRITE(NET2280_DEV_U32, &devreg->int_enable,
		   cpu_to_le32(ISL38XX_INT_IDENT_INIT));

	P54U_WRITE(NET2280_BRG_U32, NET2280_IRQSTAT1,
		   cpu_to_le32(NET2280_PCI_INTA_INTERRUPT));

	P54U_WRITE(NET2280_BRG_U32, NET2280_USBIRQENB1,
		   cpu_to_le32(NET2280_PCI_INTA_INTERRUPT_ENABLE |
			       NET2280_USB_INTERRUPT_ENABLE));

	P54U_WRITE(NET2280_DEV_U32, &devreg->dev_int,
		   cpu_to_le32(ISL38XX_DEV_INT_RESET));

	err = usb_interrupt_msg(priv->udev,
				usb_rcvbulkpipe(priv->udev, P54U_PIPE_INT),
				buf, sizeof(__le32), &alen, 1000);
	if (err || alen != sizeof(__le32))
		goto fail;

	P54U_READ(NET2280_DEV_U32, &devreg->int_ident);
	P54U_WRITE(NET2280_DEV_U32, &devreg->int_ack, reg);

	if (!(reg & cpu_to_le32(ISL38XX_INT_IDENT_INIT)))
		err = -EINVAL;

	P54U_WRITE(NET2280_BRG_U32, NET2280_USBIRQENB1, 0);
	P54U_WRITE(NET2280_BRG_U32, NET2280_IRQSTAT1,
		   cpu_to_le32(NET2280_PCI_INTA_INTERRUPT));

#undef P54U_WRITE
#undef P54U_READ

fail:
	kfree(buf);
	return err;
}