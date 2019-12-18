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
struct uniperif {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  irq; int /*<<< orphan*/ * hw; int /*<<< orphan*/ * dai_ops; int /*<<< orphan*/  state; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  UNIPERIF_STATE_STOPPED ; 
 scalar_t__ UNIPERIF_TYPE_IS_TDM (struct uniperif*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uniperif*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uni_reader_dai_ops ; 
 int /*<<< orphan*/  uni_reader_irq_handler ; 
 int /*<<< orphan*/  uni_reader_pcm_hw ; 
 int /*<<< orphan*/  uni_tdm_hw ; 

int uni_reader_init(struct platform_device *pdev,
		    struct uniperif *reader)
{
	int ret = 0;

	reader->dev = &pdev->dev;
	reader->state = UNIPERIF_STATE_STOPPED;
	reader->dai_ops = &uni_reader_dai_ops;

	if (UNIPERIF_TYPE_IS_TDM(reader))
		reader->hw = &uni_tdm_hw;
	else
		reader->hw = &uni_reader_pcm_hw;

	ret = devm_request_irq(&pdev->dev, reader->irq,
			       uni_reader_irq_handler, IRQF_SHARED,
			       dev_name(&pdev->dev), reader);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to request IRQ\n");
		return -EBUSY;
	}

	spin_lock_init(&reader->irq_lock);

	return 0;
}