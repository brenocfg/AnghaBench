#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  card; int /*<<< orphan*/ * a3d; } ;
typedef  TYPE_2__ vortex_t ;
struct TYPE_4__ {int /*<<< orphan*/  numid; } ;
struct snd_kcontrol {int /*<<< orphan*/  put; int /*<<< orphan*/  info; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRLID_FILTER ; 
 int /*<<< orphan*/  CTRLID_GAINS ; 
 int /*<<< orphan*/  CTRLID_HRTF ; 
 int /*<<< orphan*/  CTRLID_ITD ; 
 int ENOMEM ; 
 int NR_A3D ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_vortex_a3d_filter_info ; 
 int /*<<< orphan*/  snd_vortex_a3d_filter_put ; 
 int /*<<< orphan*/  snd_vortex_a3d_hrtf_info ; 
 int /*<<< orphan*/  snd_vortex_a3d_hrtf_put ; 
 int /*<<< orphan*/  snd_vortex_a3d_ild_info ; 
 int /*<<< orphan*/  snd_vortex_a3d_ild_put ; 
 int /*<<< orphan*/  snd_vortex_a3d_itd_info ; 
 int /*<<< orphan*/  snd_vortex_a3d_itd_put ; 
 int /*<<< orphan*/  vortex_a3d_kcontrol ; 

__attribute__((used)) static int vortex_a3d_register_controls(vortex_t *vortex)
{
	struct snd_kcontrol *kcontrol;
	int err, i;
	/* HRTF controls. */
	for (i = 0; i < NR_A3D; i++) {
		if ((kcontrol =
		     snd_ctl_new1(&vortex_a3d_kcontrol, &vortex->a3d[i])) == NULL)
			return -ENOMEM;
		kcontrol->id.numid = CTRLID_HRTF;
		kcontrol->info = snd_vortex_a3d_hrtf_info;
		kcontrol->put = snd_vortex_a3d_hrtf_put;
		if ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
			return err;
	}
	/* ITD controls. */
	for (i = 0; i < NR_A3D; i++) {
		if ((kcontrol =
		     snd_ctl_new1(&vortex_a3d_kcontrol, &vortex->a3d[i])) == NULL)
			return -ENOMEM;
		kcontrol->id.numid = CTRLID_ITD;
		kcontrol->info = snd_vortex_a3d_itd_info;
		kcontrol->put = snd_vortex_a3d_itd_put;
		if ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
			return err;
	}
	/* ILD (gains) controls. */
	for (i = 0; i < NR_A3D; i++) {
		if ((kcontrol =
		     snd_ctl_new1(&vortex_a3d_kcontrol, &vortex->a3d[i])) == NULL)
			return -ENOMEM;
		kcontrol->id.numid = CTRLID_GAINS;
		kcontrol->info = snd_vortex_a3d_ild_info;
		kcontrol->put = snd_vortex_a3d_ild_put;
		if ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
			return err;
	}
	/* Filter controls. */
	for (i = 0; i < NR_A3D; i++) {
		if ((kcontrol =
		     snd_ctl_new1(&vortex_a3d_kcontrol, &vortex->a3d[i])) == NULL)
			return -ENOMEM;
		kcontrol->id.numid = CTRLID_FILTER;
		kcontrol->info = snd_vortex_a3d_filter_info;
		kcontrol->put = snd_vortex_a3d_filter_put;
		if ((err = snd_ctl_add(vortex->card, kcontrol)) < 0)
			return err;
	}
	return 0;
}