#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* device; scalar_t__ audio_fd; } ;
struct TYPE_8__ {int req_samplerate; int samplerate; int blocksize; int channels; int samplesize; int bytes_per_sample; TYPE_1__ oss; } ;
typedef  TYPE_2__ audio_in_t ;

/* Variables and functions */
 int AFMT_S16_NE ; 
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_2__*,char*,int) ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int PCM_ENABLE_INPUT ; 
 int /*<<< orphan*/  SNDCTL_DSP_GETBLKSIZE ; 
 int /*<<< orphan*/  SNDCTL_DSP_GETFMTS ; 
 int /*<<< orphan*/  SNDCTL_DSP_GETTRIGGER ; 
 int /*<<< orphan*/  SNDCTL_DSP_SETFMT ; 
 int /*<<< orphan*/  SNDCTL_DSP_SETTRIGGER ; 
 int /*<<< orphan*/  SNDCTL_DSP_SPEED ; 
 scalar_t__ ai_oss_set_channels (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 
 int ioctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ open (char const*,int) ; 

int ai_oss_init(audio_in_t *ai)
{
    int err;
    int ioctl_param;

    const char *device = ai->oss.device;
    if (!device)
        device = "/dev/dsp";

    ai->oss.audio_fd = open(device, O_RDONLY | O_CLOEXEC);
    if (ai->oss.audio_fd < 0)
    {
        MP_ERR(ai, "Unable to open '%s': %s\n", device, mp_strerror(errno));
        return -1;
    }

    ioctl_param = 0 ;
    MP_VERBOSE(ai, "ioctl dsp getfmt: %d\n",
           ioctl(ai->oss.audio_fd, SNDCTL_DSP_GETFMTS, &ioctl_param));

    MP_VERBOSE(ai, "Supported formats: %x\n", ioctl_param);
    if (!(ioctl_param & AFMT_S16_NE))
        MP_ERR(ai, "unsupported format\n");

    ioctl_param = AFMT_S16_NE;
    MP_VERBOSE(ai, "ioctl dsp setfmt: %d\n",
           err = ioctl(ai->oss.audio_fd, SNDCTL_DSP_SETFMT, &ioctl_param));
    if (err < 0) {
        MP_ERR(ai, "Unable to set audio format.");
        return -1;
    }

    if (ai_oss_set_channels(ai) < 0) return -1;

    ioctl_param = ai->req_samplerate;
    MP_VERBOSE(ai, "ioctl dsp speed: %d\n",
           err = ioctl(ai->oss.audio_fd, SNDCTL_DSP_SPEED, &ioctl_param));
    if (err < 0) {
        MP_ERR(ai, "Unable to set samplerate: %d\n",
               ai->req_samplerate);
        return -1;
    }
    ai->samplerate = ioctl_param;

    MP_VERBOSE(ai, "ioctl dsp trigger: %d\n",
           ioctl(ai->oss.audio_fd, SNDCTL_DSP_GETTRIGGER, &ioctl_param));
    MP_VERBOSE(ai, "trigger: %x\n", ioctl_param);
    ioctl_param = PCM_ENABLE_INPUT;
    MP_VERBOSE(ai, "ioctl dsp trigger: %d\n",
           err = ioctl(ai->oss.audio_fd, SNDCTL_DSP_SETTRIGGER, &ioctl_param));
    if (err < 0) {
        MP_ERR(ai, "Unable to set trigger: %d\n",
               PCM_ENABLE_INPUT);
    }

    ai->blocksize = 0;
    MP_VERBOSE(ai, "ioctl dsp getblocksize: %d\n",
           err = ioctl(ai->oss.audio_fd, SNDCTL_DSP_GETBLKSIZE, &ai->blocksize));
    if (err < 0) {
        MP_ERR(ai, "Unable to get block size!\n");
    }
    MP_VERBOSE(ai, "blocksize: %d\n", ai->blocksize);

    // correct the blocksize to a reasonable value
    if (ai->blocksize <= 0) {
        ai->blocksize = 4096*ai->channels*2;
        MP_ERR(ai, "Audio block size is zero, setting to %d!\n", ai->blocksize);
    } else if (ai->blocksize < 4096*ai->channels*2) {
        ai->blocksize *= 4096*ai->channels*2/ai->blocksize;
        MP_ERR(ai, "Audio block size too low, setting to %d!\n", ai->blocksize);
    }

    ai->samplesize = 16;
    ai->bytes_per_sample = 2;

    return 0;
}