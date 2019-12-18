#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct priv {int oss_mixer_channel; int /*<<< orphan*/  oss_mixer_device; } ;
struct ao {int /*<<< orphan*/  format; struct priv* priv; } ;
typedef  enum aocontrol { ____Placeholder_aocontrol } aocontrol ;
struct TYPE_3__ {int right; int left; } ;
typedef  TYPE_1__ ao_control_vol_t ;

/* Variables and functions */
#define  AOCONTROL_GET_VOLUME 129 
#define  AOCONTROL_SET_VOLUME 128 
 int CONTROL_ERROR ; 
 int CONTROL_OK ; 
 int CONTROL_TRUE ; 
 int CONTROL_UNKNOWN ; 
 int /*<<< orphan*/  MIXER_READ (int) ; 
 int /*<<< orphan*/  MIXER_WRITE (int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SOUND_MIXER_READ_DEVMASK ; 
 int /*<<< orphan*/  af_fmt_is_pcm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int volume_oss4 (struct ao*,TYPE_1__*,int) ; 

__attribute__((used)) static int control(struct ao *ao, enum aocontrol cmd, void *arg)
{
    struct priv *p = ao->priv;
    switch (cmd) {
    case AOCONTROL_GET_VOLUME:
    case AOCONTROL_SET_VOLUME: {
        ao_control_vol_t *vol = (ao_control_vol_t *)arg;
        int fd, v, devs;

#ifdef SNDCTL_DSP_GETPLAYVOL
        // Try OSS4 first
        if (volume_oss4(ao, vol, cmd) == CONTROL_OK)
            return CONTROL_OK;
#endif

        if (!af_fmt_is_pcm(ao->format))
            return CONTROL_TRUE;

        if ((fd = open(p->oss_mixer_device, O_RDONLY)) != -1) {
            ioctl(fd, SOUND_MIXER_READ_DEVMASK, &devs);
            if (devs & (1 << p->oss_mixer_channel)) {
                if (cmd == AOCONTROL_GET_VOLUME) {
                    ioctl(fd, MIXER_READ(p->oss_mixer_channel), &v);
                    vol->right = (v & 0xFF00) >> 8;
                    vol->left = v & 0x00FF;
                } else {
                    v = ((int)vol->right << 8) | (int)vol->left;
                    ioctl(fd, MIXER_WRITE(p->oss_mixer_channel), &v);
                }
            } else {
                close(fd);
                return CONTROL_ERROR;
            }
            close(fd);
            return CONTROL_OK;
        }
        return CONTROL_ERROR;
    }
    }
    return CONTROL_UNKNOWN;
}