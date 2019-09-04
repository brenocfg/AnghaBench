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
struct snd_card {char* id; TYPE_1__* proc_root; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 int SNDRV_CARDS ; 
 scalar_t__ card_id_ok (struct snd_card*,char*) ; 
 int /*<<< orphan*/  copy_valid_id_string (struct snd_card*,char const*,char const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,scalar_t__,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void snd_card_set_id_no_lock(struct snd_card *card, const char *src,
				    const char *nid)
{
	int len, loops;
	bool is_default = false;
	char *id;
	
	copy_valid_id_string(card, src, nid);
	id = card->id;

 again:
	/* use "Default" for obviously invalid strings
	 * ("card" conflicts with proc directories)
	 */
	if (!*id || !strncmp(id, "card", 4)) {
		strcpy(id, "Default");
		is_default = true;
	}

	len = strlen(id);
	for (loops = 0; loops < SNDRV_CARDS; loops++) {
		char *spos;
		char sfxstr[5]; /* "_012" */
		int sfxlen;

		if (card_id_ok(card, id))
			return; /* OK */

		/* Add _XYZ suffix */
		sprintf(sfxstr, "_%X", loops + 1);
		sfxlen = strlen(sfxstr);
		if (len + sfxlen >= sizeof(card->id))
			spos = id + sizeof(card->id) - sfxlen - 1;
		else
			spos = id + len;
		strcpy(spos, sfxstr);
	}
	/* fallback to the default id */
	if (!is_default) {
		*id = 0;
		goto again;
	}
	/* last resort... */
	dev_err(card->dev, "unable to set card id (%s)\n", id);
	if (card->proc_root->name)
		strlcpy(card->id, card->proc_root->name, sizeof(card->id));
}