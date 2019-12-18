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
struct snd_soc_component {int dummy; } ;
struct cros_ec_codec_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int cros_ec_set_gain_range (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mic_gain_control ; 
 int snd_soc_add_component_controls (struct snd_soc_component*,int /*<<< orphan*/ *,int) ; 
 struct cros_ec_codec_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cros_ec_codec_probe(struct snd_soc_component *component)
{
	int rc;

	struct cros_ec_codec_data *codec_data =
		snd_soc_component_get_drvdata(component);

	rc = cros_ec_set_gain_range(codec_data->dev);
	if (rc)
		return rc;

	return snd_soc_add_component_controls(component, &mic_gain_control, 1);
}