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
struct audio_data {int dummy; } ;
typedef  int /*<<< orphan*/  obs_volmeter_t ;

/* Variables and functions */
 int get_nr_channels_from_audio_data (struct audio_data const*) ; 
 int /*<<< orphan*/  volmeter_process_magnitude (int /*<<< orphan*/ *,struct audio_data const*,int) ; 
 int /*<<< orphan*/  volmeter_process_peak (int /*<<< orphan*/ *,struct audio_data const*,int) ; 

__attribute__((used)) static void volmeter_process_audio_data(obs_volmeter_t *volmeter,
					const struct audio_data *data)
{
	int nr_channels = get_nr_channels_from_audio_data(data);

	volmeter_process_peak(volmeter, data, nr_channels);
	volmeter_process_magnitude(volmeter, data, nr_channels);
}