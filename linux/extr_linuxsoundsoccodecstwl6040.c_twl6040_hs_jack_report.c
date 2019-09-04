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
struct twl6040_data {int /*<<< orphan*/  mutex; } ;
struct snd_soc_jack {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int TWL6040_PLUGCOMP ; 
 int /*<<< orphan*/  TWL6040_REG_STATUS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct twl6040_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_jack_report (struct snd_soc_jack*,int,int) ; 
 int twl6040_read (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl6040_hs_jack_report(struct snd_soc_component *component,
				   struct snd_soc_jack *jack, int report)
{
	struct twl6040_data *priv = snd_soc_component_get_drvdata(component);
	int status;

	mutex_lock(&priv->mutex);

	/* Sync status */
	status = twl6040_read(component, TWL6040_REG_STATUS);
	if (status & TWL6040_PLUGCOMP)
		snd_soc_jack_report(jack, report, report);
	else
		snd_soc_jack_report(jack, 0, report);

	mutex_unlock(&priv->mutex);
}