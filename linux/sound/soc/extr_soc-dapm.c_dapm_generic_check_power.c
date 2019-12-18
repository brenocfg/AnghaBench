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
struct snd_soc_dapm_widget {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAPM_UPDATE_STAT (struct snd_soc_dapm_widget*,int /*<<< orphan*/ ) ; 
 int is_connected_input_ep (struct snd_soc_dapm_widget*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int is_connected_output_ep (struct snd_soc_dapm_widget*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_checks ; 

__attribute__((used)) static int dapm_generic_check_power(struct snd_soc_dapm_widget *w)
{
	int in, out;

	DAPM_UPDATE_STAT(w, power_checks);

	in = is_connected_input_ep(w, NULL, NULL);
	out = is_connected_output_ep(w, NULL, NULL);
	return out != 0 && in != 0;
}