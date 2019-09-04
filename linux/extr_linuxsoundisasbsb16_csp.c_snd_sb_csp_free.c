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
struct snd_sb_csp {int running; int /*<<< orphan*/ * csp_programs; } ;
struct snd_hwdep {struct snd_sb_csp* private_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int SNDRV_SB_CSP_ST_RUNNING ; 
 int /*<<< orphan*/  kfree (struct snd_sb_csp*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sb_csp_stop (struct snd_sb_csp*) ; 

__attribute__((used)) static void snd_sb_csp_free(struct snd_hwdep *hwdep)
{
	int i;
	struct snd_sb_csp *p = hwdep->private_data;
	if (p) {
		if (p->running & SNDRV_SB_CSP_ST_RUNNING)
			snd_sb_csp_stop(p);
		for (i = 0; i < ARRAY_SIZE(p->csp_programs); ++i)
			release_firmware(p->csp_programs[i]);
		kfree(p);
	}
}