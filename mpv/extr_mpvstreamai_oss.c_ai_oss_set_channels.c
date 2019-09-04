#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  audio_fd; } ;
struct TYPE_7__ {int req_channels; int channels; TYPE_1__ oss; } ;
typedef  TYPE_2__ audio_in_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,int,...) ; 
 int /*<<< orphan*/  SNDCTL_DSP_CHANNELS ; 
 int /*<<< orphan*/  SNDCTL_DSP_STEREO ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int ai_oss_set_channels(audio_in_t *ai)
{
    int err;
    int ioctl_param;

    if (ai->req_channels > 2)
    {
        ioctl_param = ai->req_channels;
        MP_VERBOSE(ai, "ioctl dsp channels: %d\n",
               err = ioctl(ai->oss.audio_fd, SNDCTL_DSP_CHANNELS, &ioctl_param));
        if (err < 0) {
            MP_ERR(ai, "Unable to set channel count: %d\n",
                   ai->req_channels);
            return -1;
        }
        ai->channels = ioctl_param;
    }
    else
    {
        ioctl_param = (ai->req_channels == 2);
        MP_VERBOSE(ai, "ioctl dsp stereo: %d (req: %d)\n",
               err = ioctl(ai->oss.audio_fd, SNDCTL_DSP_STEREO, &ioctl_param),
               ioctl_param);
        if (err < 0) {
            MP_ERR(ai, "Unable to set stereo: %d\n",
                   ai->req_channels == 2);
            return -1;
        }
        ai->channels = ioctl_param ? 2 : 1;
    }
    return 0;
}