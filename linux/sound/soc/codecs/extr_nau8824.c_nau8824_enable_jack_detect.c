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
struct snd_soc_jack {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct nau8824 {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  jdet_work; struct snd_soc_jack* jack; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct nau8824*) ; 
 int /*<<< orphan*/  nau8824_interrupt ; 
 int /*<<< orphan*/  nau8824_jdet_work ; 
 struct nau8824* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int nau8824_enable_jack_detect(struct snd_soc_component *component,
	struct snd_soc_jack *jack)
{
	struct nau8824 *nau8824 = snd_soc_component_get_drvdata(component);
	int ret;

	nau8824->jack = jack;
	/* Initiate jack detection work queue */
	INIT_WORK(&nau8824->jdet_work, nau8824_jdet_work);
	ret = devm_request_threaded_irq(nau8824->dev, nau8824->irq, NULL,
		nau8824_interrupt, IRQF_TRIGGER_LOW | IRQF_ONESHOT,
		"nau8824", nau8824);
	if (ret) {
		dev_err(nau8824->dev, "Cannot request irq %d (%d)\n",
			nau8824->irq, ret);
	}

	return ret;
}