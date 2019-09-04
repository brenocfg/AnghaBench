#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wm_coeff_ctl {int flags; int set; TYPE_3__* dsp; int /*<<< orphan*/  len; scalar_t__ enabled; int /*<<< orphan*/  cache; } ;
struct soc_bytes_ext {int dummy; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_4__ {char* data; } ;
struct TYPE_5__ {TYPE_1__ bytes; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  pwr_lock; scalar_t__ running; } ;

/* Variables and functions */
 int EPERM ; 
 int WMFW_CTL_FLAG_VOLATILE ; 
 struct wm_coeff_ctl* bytes_ext_to_ctl (struct soc_bytes_ext*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wm_coeff_write_control (struct wm_coeff_ctl*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm_coeff_put(struct snd_kcontrol *kctl,
			struct snd_ctl_elem_value *ucontrol)
{
	struct soc_bytes_ext *bytes_ext =
		(struct soc_bytes_ext *)kctl->private_value;
	struct wm_coeff_ctl *ctl = bytes_ext_to_ctl(bytes_ext);
	char *p = ucontrol->value.bytes.data;
	int ret = 0;

	mutex_lock(&ctl->dsp->pwr_lock);

	if (ctl->flags & WMFW_CTL_FLAG_VOLATILE)
		ret = -EPERM;
	else
		memcpy(ctl->cache, p, ctl->len);

	ctl->set = 1;
	if (ctl->enabled && ctl->dsp->running)
		ret = wm_coeff_write_control(ctl, p, ctl->len);

	mutex_unlock(&ctl->dsp->pwr_lock);

	return ret;
}