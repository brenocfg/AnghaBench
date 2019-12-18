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
struct hdspm {int dummy; } ;

/* Variables and functions */
 int HDSPM_MIXER_CHANNELS ; 
 int UNITY_GAIN ; 
 int /*<<< orphan*/  hdspm_write_in_gain (struct hdspm*,int,int,unsigned int) ; 
 int /*<<< orphan*/  hdspm_write_pb_gain (struct hdspm*,int,int,unsigned int) ; 

__attribute__((used)) static void all_in_all_mixer(struct hdspm * hdspm, int sgain)
{
	int i, j;
	unsigned int gain;

	if (sgain > UNITY_GAIN)
		gain = UNITY_GAIN;
	else if (sgain < 0)
		gain = 0;
	else
		gain = sgain;

	for (i = 0; i < HDSPM_MIXER_CHANNELS; i++)
		for (j = 0; j < HDSPM_MIXER_CHANNELS; j++) {
			hdspm_write_in_gain(hdspm, i, j, gain);
			hdspm_write_pb_gain(hdspm, i, j, gain);
		}
}