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
struct priv {int /*<<< orphan*/  audio_fd; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int AFMT_AC3 ; 
 int /*<<< orphan*/  MP_ERR (struct ao*,char*,int) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_WARN (struct ao*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDCTL_DSP_SETFMT ; 
 scalar_t__ af_fmt_is_spdif (int) ; 
 int /*<<< orphan*/  af_fmt_to_str (int) ; 
 int format2oss (int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int oss2format (int) ; 

__attribute__((used)) static bool try_format(struct ao *ao, int *format)
{
    struct priv *p = ao->priv;

    int oss_format = format2oss(*format);
    if (oss_format == -1 && af_fmt_is_spdif(*format))
        oss_format = AFMT_AC3;

    if (oss_format == -1) {
        MP_VERBOSE(ao, "Unknown/not supported internal format: %s\n",
                   af_fmt_to_str(*format));
        *format = 0;
        return false;
    }

    int actual_format = oss_format;
    if (ioctl(p->audio_fd, SNDCTL_DSP_SETFMT, &actual_format) < 0)
        actual_format = -1;

    if (actual_format == oss_format)
        return true;

    MP_WARN(ao, "Can't set audio device to %s output.\n", af_fmt_to_str(*format));
    *format = oss2format(actual_format);
    if (actual_format != -1 && !*format)
        MP_ERR(ao, "Unknown/Unsupported OSS format: 0x%x.\n", actual_format);
    return false;
}