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
struct fsl_asrc {TYPE_2__** pair; int /*<<< orphan*/  regmap; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum asrc_pair_index { ____Placeholder_asrc_pair_index } asrc_pair_index ;
struct TYPE_4__ {int /*<<< orphan*/  error; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASRC_INPUT_BUFFER_UNDERRUN ; 
 int /*<<< orphan*/  ASRC_INPUT_TASK_OVERLOAD ; 
 int /*<<< orphan*/  ASRC_OUTPUT_BUFFER_OVERFLOW ; 
 int /*<<< orphan*/  ASRC_OUTPUT_TASK_OVERLOAD ; 
 int ASRC_PAIR_A ; 
 int ASRC_PAIR_MAX_NUM ; 
 int /*<<< orphan*/  ASRC_TASK_Q_OVERLOAD ; 
 int ASRSTR_AIDU (int) ; 
 int ASRSTR_AIOL (int) ; 
 int ASRSTR_AODO (int) ; 
 int /*<<< orphan*/  ASRSTR_AOLE ; 
 int ASRSTR_AOOL (int) ; 
 int ASRSTR_ATQOL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_ASRSTR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  pair_dbg (char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t fsl_asrc_isr(int irq, void *dev_id)
{
	struct fsl_asrc *asrc_priv = (struct fsl_asrc *)dev_id;
	struct device *dev = &asrc_priv->pdev->dev;
	enum asrc_pair_index index;
	u32 status;

	regmap_read(asrc_priv->regmap, REG_ASRSTR, &status);

	/* Clean overload error */
	regmap_write(asrc_priv->regmap, REG_ASRSTR, ASRSTR_AOLE);

	/*
	 * We here use dev_dbg() for all exceptions because ASRC itself does
	 * not care if FIFO overflowed or underrun while a warning in the
	 * interrupt would result a ridged conversion.
	 */
	for (index = ASRC_PAIR_A; index < ASRC_PAIR_MAX_NUM; index++) {
		if (!asrc_priv->pair[index])
			continue;

		if (status & ASRSTR_ATQOL) {
			asrc_priv->pair[index]->error |= ASRC_TASK_Q_OVERLOAD;
			dev_dbg(dev, "ASRC Task Queue FIFO overload\n");
		}

		if (status & ASRSTR_AOOL(index)) {
			asrc_priv->pair[index]->error |= ASRC_OUTPUT_TASK_OVERLOAD;
			pair_dbg("Output Task Overload\n");
		}

		if (status & ASRSTR_AIOL(index)) {
			asrc_priv->pair[index]->error |= ASRC_INPUT_TASK_OVERLOAD;
			pair_dbg("Input Task Overload\n");
		}

		if (status & ASRSTR_AODO(index)) {
			asrc_priv->pair[index]->error |= ASRC_OUTPUT_BUFFER_OVERFLOW;
			pair_dbg("Output Data Buffer has overflowed\n");
		}

		if (status & ASRSTR_AIDU(index)) {
			asrc_priv->pair[index]->error |= ASRC_INPUT_BUFFER_UNDERRUN;
			pair_dbg("Input Data Buffer has underflowed\n");
		}
	}

	return IRQ_HANDLED;
}