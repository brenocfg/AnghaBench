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
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_data_set_default_string (int /*<<< orphan*/ *,char*,char*) ; 

void alsa_get_defaults(obs_data_t *settings)
{
	obs_data_set_default_string(settings, "device_id", "default");
	obs_data_set_default_string(settings, "custom_pcm", "default");
	obs_data_set_default_int(settings, "rate", 44100);
}