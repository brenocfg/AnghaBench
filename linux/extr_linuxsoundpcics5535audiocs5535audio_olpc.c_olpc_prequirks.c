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
struct snd_card {int dummy; } ;
struct snd_ac97_template {int /*<<< orphan*/  scaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_SCAP_INV_EAPD ; 
 int /*<<< orphan*/  machine_is_olpc () ; 
 scalar_t__ olpc_board_at_least (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  olpc_board_pre (int) ; 

void olpc_prequirks(struct snd_card *card,
		    struct snd_ac97_template *ac97)
{
	if (!machine_is_olpc())
		return;

	/* invert EAPD if on an OLPC B3 or higher */
	if (olpc_board_at_least(olpc_board_pre(0xb3)))
		ac97->scaps |= AC97_SCAP_INV_EAPD;
}