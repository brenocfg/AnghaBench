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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ast_vhub {int /*<<< orphan*/ * ep0_bufs; int /*<<< orphan*/  ep0_bufs_dma; int /*<<< orphan*/  lock; scalar_t__ clk; scalar_t__ regs; TYPE_1__* ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_CTRL ; 
 int AST_VHUB_EP0_MAX_PACKET ; 
 scalar_t__ AST_VHUB_IER ; 
 scalar_t__ AST_VHUB_ISR ; 
 int AST_VHUB_NUM_PORTS ; 
 int VHUB_CTRL_PHY_CLK ; 
 int VHUB_CTRL_PHY_RESET_DIS ; 
 int VHUB_IRQ_ACK_ALL ; 
 int /*<<< orphan*/  ast_vhub_del_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ast_vhub* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ast_vhub_remove(struct platform_device *pdev)
{
	struct ast_vhub *vhub = platform_get_drvdata(pdev);
	unsigned long flags;
	int i;

	if (!vhub || !vhub->regs)
		return 0;

	/* Remove devices */
	for (i = 0; i < AST_VHUB_NUM_PORTS; i++)
		ast_vhub_del_dev(&vhub->ports[i].dev);

	spin_lock_irqsave(&vhub->lock, flags);

	/* Mask & ack all interrupts  */
	writel(0, vhub->regs + AST_VHUB_IER);
	writel(VHUB_IRQ_ACK_ALL, vhub->regs + AST_VHUB_ISR);

	/* Pull device, leave PHY enabled */
	writel(VHUB_CTRL_PHY_CLK |
	       VHUB_CTRL_PHY_RESET_DIS,
	       vhub->regs + AST_VHUB_CTRL);

	if (vhub->clk)
		clk_disable_unprepare(vhub->clk);

	spin_unlock_irqrestore(&vhub->lock, flags);

	if (vhub->ep0_bufs)
		dma_free_coherent(&pdev->dev,
				  AST_VHUB_EP0_MAX_PACKET *
				  (AST_VHUB_NUM_PORTS + 1),
				  vhub->ep0_bufs,
				  vhub->ep0_bufs_dma);
	vhub->ep0_bufs = NULL;

	return 0;
}