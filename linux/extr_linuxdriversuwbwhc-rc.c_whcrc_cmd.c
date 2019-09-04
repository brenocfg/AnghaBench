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
typedef  size_t u32 ;
struct whcrc {int /*<<< orphan*/  irq_lock; scalar_t__ rc_base; int /*<<< orphan*/  cmd_dma_buf; int /*<<< orphan*/  cmd_buf; int /*<<< orphan*/  cmd_wq; TYPE_1__* umc_dev; } ;
struct uwb_rccb {int dummy; } ;
struct uwb_rc {struct whcrc* priv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int HZ ; 
 scalar_t__ URCCMD ; 
 scalar_t__ URCCMDADDR ; 
 size_t URCCMD_ACTIVE ; 
 size_t URCCMD_EARV ; 
 size_t URCCMD_IWR ; 
 size_t URCCMD_SIZE_MASK ; 
 scalar_t__ URCSTS ; 
 int URCSTS_HALTED ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 size_t le_readl (scalar_t__) ; 
 int /*<<< orphan*/  le_writel (size_t,scalar_t__) ; 
 int /*<<< orphan*/  le_writeq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,struct uwb_rccb const*,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_rc_reset_all (struct uwb_rc*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int whcrc_cmd(struct uwb_rc *uwb_rc,
	      const struct uwb_rccb *cmd, size_t cmd_size)
{
	int result = 0;
	struct whcrc *whcrc = uwb_rc->priv;
	struct device *dev = &whcrc->umc_dev->dev;
	u32 urccmd;

	if (cmd_size >= 4096)
		return -EINVAL;

	/*
	 * If the URC is halted, then the hardware has reset itself.
	 * Attempt to recover by restarting the device and then return
	 * an error as it's likely that the current command isn't
	 * valid for a newly started RC.
	 */
	if (le_readl(whcrc->rc_base + URCSTS) & URCSTS_HALTED) {
		dev_err(dev, "requesting reset of halted radio controller\n");
		uwb_rc_reset_all(uwb_rc);
		return -EIO;
	}

	result = wait_event_timeout(whcrc->cmd_wq,
		!(le_readl(whcrc->rc_base + URCCMD) & URCCMD_ACTIVE), HZ/2);
	if (result == 0) {
		dev_err(dev, "device is not ready to execute commands\n");
		return -ETIMEDOUT;
	}

	memmove(whcrc->cmd_buf, cmd, cmd_size);
	le_writeq(whcrc->cmd_dma_buf, whcrc->rc_base + URCCMDADDR);

	spin_lock(&whcrc->irq_lock);
	urccmd = le_readl(whcrc->rc_base + URCCMD);
	urccmd &= ~(URCCMD_EARV | URCCMD_SIZE_MASK);
	le_writel(urccmd | URCCMD_ACTIVE | URCCMD_IWR | cmd_size,
		  whcrc->rc_base + URCCMD);
	spin_unlock(&whcrc->irq_lock);

	return 0;
}