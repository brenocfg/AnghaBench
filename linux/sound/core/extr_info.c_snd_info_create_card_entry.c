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
struct snd_info_entry {int dummy; } ;
struct snd_card {int /*<<< orphan*/  module; struct snd_info_entry* proc_root; } ;

/* Variables and functions */
 struct snd_info_entry* snd_info_create_entry (char const*,struct snd_info_entry*,int /*<<< orphan*/ ) ; 

struct snd_info_entry *snd_info_create_card_entry(struct snd_card *card,
					     const char *name,
					     struct snd_info_entry * parent)
{
	if (!parent)
		parent = card->proc_root;
	return snd_info_create_entry(name, parent, card->module);
}