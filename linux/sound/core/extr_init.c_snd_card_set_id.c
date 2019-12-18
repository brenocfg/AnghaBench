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
struct snd_card {char* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_mutex ; 
 int /*<<< orphan*/  snd_card_set_id_no_lock (struct snd_card*,char const*,char const*) ; 

void snd_card_set_id(struct snd_card *card, const char *nid)
{
	/* check if user specified own card->id */
	if (card->id[0] != '\0')
		return;
	mutex_lock(&snd_card_mutex);
	snd_card_set_id_no_lock(card, nid, nid);
	mutex_unlock(&snd_card_mutex);
}