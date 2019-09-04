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
struct snd_soc_card {int /*<<< orphan*/  snd_card; } ;

/* Variables and functions */
 int pisnd_ctl_init (int /*<<< orphan*/ ) ; 
 int pisnd_midi_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printe (char*,int) ; 

__attribute__((used)) static int pisnd_card_probe(struct snd_soc_card *card)
{
	int err = pisnd_midi_init(card->snd_card);

	if (err < 0) {
		printe("pisnd_midi_init failed: %d\n", err);
		return err;
	}

	err = pisnd_ctl_init(card->snd_card);
	if (err < 0) {
		printe("pisnd_ctl_init failed: %d\n", err);
		return err;
	}

	return 0;
}