#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* release; void* ioctl_compat; void* ioctl; void* open; } ;
struct snd_hwdep {TYPE_1__ ops; int /*<<< orphan*/  name; struct hdspm* private_data; } ;
struct snd_card {int dummy; } ;
struct hdspm {struct snd_hwdep* hwdep; } ;

/* Variables and functions */
 void* snd_hdspm_hwdep_dummy_op ; 
 void* snd_hdspm_hwdep_ioctl ; 
 int snd_hwdep_new (struct snd_card*,char*,int /*<<< orphan*/ ,struct snd_hwdep**) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_hdspm_create_hwdep(struct snd_card *card,
				  struct hdspm *hdspm)
{
	struct snd_hwdep *hw;
	int err;

	err = snd_hwdep_new(card, "HDSPM hwdep", 0, &hw);
	if (err < 0)
		return err;

	hdspm->hwdep = hw;
	hw->private_data = hdspm;
	strcpy(hw->name, "HDSPM hwdep interface");

	hw->ops.open = snd_hdspm_hwdep_dummy_op;
	hw->ops.ioctl = snd_hdspm_hwdep_ioctl;
	hw->ops.ioctl_compat = snd_hdspm_hwdep_ioctl;
	hw->ops.release = snd_hdspm_hwdep_dummy_op;

	return 0;
}