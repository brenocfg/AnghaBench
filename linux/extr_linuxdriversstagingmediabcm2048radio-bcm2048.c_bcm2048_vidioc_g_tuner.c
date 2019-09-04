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
struct v4l2_tuner {scalar_t__ index; int capability; int signal; scalar_t__ afc; int /*<<< orphan*/  audmode; int /*<<< orphan*/  rxsubchans; void* rangehigh; void* rangelow; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct bcm2048_device {scalar_t__ power_state; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 scalar_t__ BCM2048_FREQ_ERROR_FLOOR ; 
 scalar_t__ BCM2048_FREQ_ERROR_ROOF ; 
 scalar_t__ BCM2048_RSSI_LEVEL_BASE ; 
 scalar_t__ BCM2048_RSSI_LEVEL_ROOF ; 
 scalar_t__ BCM2048_RSSI_LEVEL_ROOF_NEG ; 
 scalar_t__ BCM2048_SIGNAL_MULTIPLIER ; 
 int EINVAL ; 
 int ENODEV ; 
 int V4L2_TUNER_CAP_LOW ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 scalar_t__ bcm2048_get_fm_carrier_error (struct bcm2048_device*) ; 
 scalar_t__ bcm2048_get_fm_rssi (struct bcm2048_device*) ; 
 int /*<<< orphan*/  bcm2048_get_region_bottom_frequency (struct bcm2048_device*) ; 
 int /*<<< orphan*/  bcm2048_get_region_top_frequency (struct bcm2048_device*) ; 
 void* dev_to_v4l2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct bcm2048_device* video_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2048_vidioc_g_tuner(struct file *file, void *priv,
				  struct v4l2_tuner *tuner)
{
	struct bcm2048_device *bdev = video_get_drvdata(video_devdata(file));
	s8 f_error;
	s8 rssi;

	if (!bdev)
		return -ENODEV;

	if (tuner->index > 0)
		return -EINVAL;

	strncpy(tuner->name, "FM Receiver", 32);
	tuner->type = V4L2_TUNER_RADIO;
	tuner->rangelow =
		dev_to_v4l2(bcm2048_get_region_bottom_frequency(bdev));
	tuner->rangehigh =
		dev_to_v4l2(bcm2048_get_region_top_frequency(bdev));
	tuner->rxsubchans = V4L2_TUNER_SUB_STEREO;
	tuner->capability = V4L2_TUNER_CAP_STEREO | V4L2_TUNER_CAP_LOW;
	tuner->audmode = V4L2_TUNER_MODE_STEREO;
	tuner->afc = 0;
	if (bdev->power_state) {
		/*
		 * Report frequencies with high carrier errors to have zero
		 * signal level
		 */
		f_error = bcm2048_get_fm_carrier_error(bdev);
		if (f_error < BCM2048_FREQ_ERROR_FLOOR ||
		    f_error > BCM2048_FREQ_ERROR_ROOF) {
			tuner->signal = 0;
		} else {
			/*
			 * RSSI level -60 dB is defined to report full
			 * signal strength
			 */
			rssi = bcm2048_get_fm_rssi(bdev);
			if (rssi >= BCM2048_RSSI_LEVEL_BASE) {
				tuner->signal = 0xFFFF;
			} else if (rssi > BCM2048_RSSI_LEVEL_ROOF) {
				tuner->signal = (rssi +
						 BCM2048_RSSI_LEVEL_ROOF_NEG)
						 * BCM2048_SIGNAL_MULTIPLIER;
			} else {
				tuner->signal = 0;
			}
		}
	} else {
		tuner->signal = 0;
	}

	return 0;
}