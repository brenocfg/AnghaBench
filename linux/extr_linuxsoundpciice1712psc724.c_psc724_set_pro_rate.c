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
struct snd_ice1712 {struct psc724_spec* spec; } ;
struct psc724_spec {int /*<<< orphan*/  wm8766; int /*<<< orphan*/  wm8776; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_wm8766_volume_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_wm8776_volume_restore (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void psc724_set_pro_rate(struct snd_ice1712 *ice, unsigned int rate)
{
	struct psc724_spec *spec = ice->spec;
	/* restore codec volume settings after rate change (PMCLK stop) */
	snd_wm8776_volume_restore(&spec->wm8776);
	snd_wm8766_volume_restore(&spec->wm8766);
}