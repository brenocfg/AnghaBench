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
struct priv {char* cfg_oss_mixer_channel; int oss_mixer_channel; int buffersize; int outburst; int /*<<< orphan*/  audio_fd; int /*<<< orphan*/  oss_mixer_device; } ;
struct ao {int /*<<< orphan*/  format; struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct ao*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int SOUND_MIXER_NRDEVICES ; 
 int SOUND_MIXER_PCM ; 
 int /*<<< orphan*/  SOUND_MIXER_READ_DEVMASK ; 
 int /*<<< orphan*/  af_fmt_from_planar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ device_writable (struct ao*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ,int*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * mixer_channels ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reopen_device (struct ao*,int) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  uninit (struct ao*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int init(struct ao *ao)
{
    struct priv *p = ao->priv;

    const char *mchan = NULL;
    if (p->cfg_oss_mixer_channel && p->cfg_oss_mixer_channel[0])
        mchan = p->cfg_oss_mixer_channel;

    if (mchan) {
        int fd, devs, i;

        if ((fd = open(p->oss_mixer_device, O_RDONLY)) == -1) {
            MP_ERR(ao, "Can't open mixer device %s: %s\n",
                   p->oss_mixer_device, mp_strerror(errno));
        } else {
            ioctl(fd, SOUND_MIXER_READ_DEVMASK, &devs);
            close(fd);

            for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
                if (!strcasecmp(mixer_channels[i], mchan)) {
                    if (!(devs & (1 << i))) {
                        MP_ERR(ao, "Audio card mixer does not have "
                               "channel '%s', using default.\n", mchan);
                        i = SOUND_MIXER_NRDEVICES + 1;
                        break;
                    }
                    p->oss_mixer_channel = i;
                    break;
                }
            }
            if (i == SOUND_MIXER_NRDEVICES) {
                MP_ERR(ao, "Audio card mixer does not have "
                       "channel '%s', using default.\n", mchan);
            }
        }
    } else {
        p->oss_mixer_channel = SOUND_MIXER_PCM;
    }

    MP_VERBOSE(ao, "using '%s' mixer device\n", p->oss_mixer_device);
    MP_VERBOSE(ao, "using '%s' mixer channel\n", mixer_channels[p->oss_mixer_channel]);

    ao->format = af_fmt_from_planar(ao->format);

    if (reopen_device(ao, true) < 0)
        goto fail;

    if (p->buffersize == -1) {
        // Measuring buffer size:
        void *data = malloc(p->outburst);
        if (!data) {
            MP_ERR(ao, "Out of memory, or broken outburst size.\n");
            goto fail;
        }
        p->buffersize = 0;
        memset(data, 0, p->outburst);
        while (p->buffersize < 0x40000 && device_writable(ao) > 0) {
            (void)write(p->audio_fd, data, p->outburst);
            p->buffersize += p->outburst;
        }
        free(data);
        if (p->buffersize == 0) {
            MP_ERR(ao, "Your OSS audio driver DOES NOT support poll().\n");
            goto fail;
        }
    }

    return 0;

fail:
    uninit(ao);
    return -1;
}