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
struct snd_soc_component {TYPE_1__* card; int /*<<< orphan*/  dev; } ;
struct cx20442_priv {int /*<<< orphan*/ * tty; int /*<<< orphan*/  por; } ;
struct TYPE_2__ {scalar_t__ pop_time; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct cx20442_priv*) ; 
 struct cx20442_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,struct cx20442_priv*) ; 

__attribute__((used)) static int cx20442_component_probe(struct snd_soc_component *component)
{
	struct cx20442_priv *cx20442;

	cx20442 = kzalloc(sizeof(struct cx20442_priv), GFP_KERNEL);
	if (cx20442 == NULL)
		return -ENOMEM;

	cx20442->por = regulator_get(component->dev, "POR");
	if (IS_ERR(cx20442->por)) {
		int err = PTR_ERR(cx20442->por);

		dev_warn(component->dev, "failed to get POR supply (%d)", err);
		/*
		 * When running on a non-dt platform and requested regulator
		 * is not available, regulator_get() never returns
		 * -EPROBE_DEFER as it is not able to justify if the regulator
		 * may still appear later.  On the other hand, the board can
		 * still set full constraints flag at late_initcall in order
		 * to instruct regulator_get() to return a dummy one if
		 * sufficient.  Hence, if we get -ENODEV here, let's convert
		 * it to -EPROBE_DEFER and wait for the board to decide or
		 * let Deferred Probe infrastructure handle this error.
		 */
		if (err == -ENODEV)
			err = -EPROBE_DEFER;
		kfree(cx20442);
		return err;
	}

	cx20442->tty = NULL;

	snd_soc_component_set_drvdata(component, cx20442);
	component->card->pop_time = 0;

	return 0;
}