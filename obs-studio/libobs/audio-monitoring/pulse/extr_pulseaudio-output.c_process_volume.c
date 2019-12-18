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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct audio_monitor {int bytes_per_channel; int /*<<< orphan*/  channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  process_byte (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  process_float (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  process_short (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 

void process_volume(const struct audio_monitor *monitor, float vol,
		    uint8_t *const *resample_data, uint32_t resample_frames)
{
	switch (monitor->bytes_per_channel) {
	case 1:
		process_byte(resample_data[0], resample_frames,
			     monitor->channels, vol);
		break;
	case 2:
		process_short(resample_data[0], resample_frames,
			      monitor->channels, vol);
		break;
	default:
		process_float(resample_data[0], resample_frames,
			      monitor->channels, vol);
		break;
	}
}