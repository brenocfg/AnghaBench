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
struct gain_data {int /*<<< orphan*/  multiple; int /*<<< orphan*/  channels; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  S_GAIN_DB ; 
 int /*<<< orphan*/  audio_output_get_channels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_to_mul (float) ; 
 double obs_data_get_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_get_audio () ; 

__attribute__((used)) static void gain_update(void *data, obs_data_t *s)
{
	struct gain_data *gf = data;
	double val = obs_data_get_double(s, S_GAIN_DB);
	gf->channels = audio_output_get_channels(obs_get_audio());
	gf->multiple = db_to_mul((float)val);
}