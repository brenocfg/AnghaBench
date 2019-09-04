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
struct snd_card {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct snd_card** snd_cards ; 
 int snd_ecards_limit ; 
 int /*<<< orphan*/  snd_info_check_reserved_words (char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool card_id_ok(struct snd_card *card, const char *id)
{
	int i;
	if (!snd_info_check_reserved_words(id))
		return false;
	for (i = 0; i < snd_ecards_limit; i++) {
		if (snd_cards[i] && snd_cards[i] != card &&
		    !strcmp(snd_cards[i]->id, id))
			return false;
	}
	return true;
}