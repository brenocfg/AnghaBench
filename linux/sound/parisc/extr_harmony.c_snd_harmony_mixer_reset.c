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
struct TYPE_2__ {int /*<<< orphan*/  gain; } ;
struct snd_harmony {TYPE_1__ st; } ;

/* Variables and functions */
 int /*<<< orphan*/  HARMONY_GAIN_DEFAULT ; 
 int /*<<< orphan*/  harmony_mute (struct snd_harmony*) ; 
 int /*<<< orphan*/  harmony_reset (struct snd_harmony*) ; 
 int /*<<< orphan*/  harmony_unmute (struct snd_harmony*) ; 

__attribute__((used)) static void
snd_harmony_mixer_reset(struct snd_harmony *h)
{
	harmony_mute(h);
	harmony_reset(h);
	h->st.gain = HARMONY_GAIN_DEFAULT;
	harmony_unmute(h);
}