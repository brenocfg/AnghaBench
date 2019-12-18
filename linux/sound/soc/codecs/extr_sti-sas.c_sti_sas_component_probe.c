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
struct sti_sas_data {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct sti_sas_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int sti_sas_init_sas_registers (struct snd_soc_component*,struct sti_sas_data*) ; 

__attribute__((used)) static int sti_sas_component_probe(struct snd_soc_component *component)
{
	struct sti_sas_data *drvdata = dev_get_drvdata(component->dev);
	int ret;

	ret = sti_sas_init_sas_registers(component, drvdata);

	return ret;
}