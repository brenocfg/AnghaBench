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
struct snd_sb_csp {int running; scalar_t__ mode; scalar_t__ acc_rates; scalar_t__ acc_width; scalar_t__ acc_channels; scalar_t__ acc_format; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 scalar_t__ SNDRV_SB_CSP_MODE_QSOUND ; 
 int SNDRV_SB_CSP_ST_LOADED ; 
 int SNDRV_SB_CSP_ST_RUNNING ; 
 int /*<<< orphan*/  snd_sb_qsound_destroy (struct snd_sb_csp*) ; 

__attribute__((used)) static int snd_sb_csp_unload(struct snd_sb_csp * p)
{
	if (p->running & SNDRV_SB_CSP_ST_RUNNING)
		return -EBUSY;
	if (!(p->running & SNDRV_SB_CSP_ST_LOADED))
		return -ENXIO;

	/* clear supported formats */
	p->acc_format = 0;
	p->acc_channels = p->acc_width = p->acc_rates = 0;
	/* destroy QSound mixer element */
	if (p->mode == SNDRV_SB_CSP_MODE_QSOUND) {
		snd_sb_qsound_destroy(p);
	}
	/* clear all flags */
	p->running = 0;
	p->mode = 0;
	return 0;
}