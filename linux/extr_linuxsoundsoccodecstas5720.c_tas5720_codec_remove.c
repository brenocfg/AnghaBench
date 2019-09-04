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
struct tas5720_data {int /*<<< orphan*/  supplies; int /*<<< orphan*/  fault_check_work; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tas5720_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void tas5720_codec_remove(struct snd_soc_component *component)
{
	struct tas5720_data *tas5720 = snd_soc_component_get_drvdata(component);
	int ret;

	cancel_delayed_work_sync(&tas5720->fault_check_work);

	ret = regulator_bulk_disable(ARRAY_SIZE(tas5720->supplies),
				     tas5720->supplies);
	if (ret < 0)
		dev_err(component->dev, "failed to disable supplies: %d\n", ret);
}