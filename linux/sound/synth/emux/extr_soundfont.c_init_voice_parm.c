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
struct soundfont_voice_parm {int moddelay; int modatkhld; int moddcysus; int modrelease; int voldelay; int volatkhld; int voldcysus; int volrelease; int lfo1delay; int lfo2delay; int cutoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct soundfont_voice_parm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
init_voice_parm(struct soundfont_voice_parm *pp)
{
	memset(pp, 0, sizeof(*pp));

	pp->moddelay = 0x8000;
	pp->modatkhld = 0x7f7f;
	pp->moddcysus = 0x7f7f;
	pp->modrelease = 0x807f;

	pp->voldelay = 0x8000;
	pp->volatkhld = 0x7f7f;
	pp->voldcysus = 0x7f7f;
	pp->volrelease = 0x807f;

	pp->lfo1delay = 0x8000;
	pp->lfo2delay = 0x8000;

	pp->cutoff = 0xff;
}