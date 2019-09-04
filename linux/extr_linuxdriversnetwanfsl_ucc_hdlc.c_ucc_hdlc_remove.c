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
struct ucc_hdlc_private {TYPE_1__* utdm; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * siram; int /*<<< orphan*/ * si_regs; } ;

/* Variables and functions */
 struct ucc_hdlc_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ucc_hdlc_private*) ; 
 int /*<<< orphan*/  uhdlc_memclean (struct ucc_hdlc_private*) ; 

__attribute__((used)) static int ucc_hdlc_remove(struct platform_device *pdev)
{
	struct ucc_hdlc_private *priv = dev_get_drvdata(&pdev->dev);

	uhdlc_memclean(priv);

	if (priv->utdm->si_regs) {
		iounmap(priv->utdm->si_regs);
		priv->utdm->si_regs = NULL;
	}

	if (priv->utdm->siram) {
		iounmap(priv->utdm->siram);
		priv->utdm->siram = NULL;
	}
	kfree(priv);

	dev_info(&pdev->dev, "UCC based hdlc module removed\n");

	return 0;
}