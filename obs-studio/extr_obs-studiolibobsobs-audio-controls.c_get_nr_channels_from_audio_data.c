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
struct audio_data {scalar_t__* data; } ;

/* Variables and functions */
 int CLAMP (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_AUDIO_CHANNELS ; 
 int MAX_AV_PLANES ; 

__attribute__((used)) static int get_nr_channels_from_audio_data(const struct audio_data *data)
{
	int nr_channels = 0;
	for (int i = 0; i < MAX_AV_PLANES; i++) {
		if (data->data[i])
			nr_channels++;
	}
	return CLAMP(nr_channels, 0, MAX_AUDIO_CHANNELS);
}