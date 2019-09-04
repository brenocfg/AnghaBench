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
struct snd_trident {scalar_t__ device; int /*<<< orphan*/  card; } ;
struct snd_info_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ TRIDENT_DEVICE_ID_SI7018 ; 
 int /*<<< orphan*/  snd_card_proc_new (int /*<<< orphan*/ ,char const*,struct snd_info_entry**) ; 
 int /*<<< orphan*/  snd_info_set_text_ops (struct snd_info_entry*,struct snd_trident*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_trident_proc_read ; 

__attribute__((used)) static void snd_trident_proc_init(struct snd_trident *trident)
{
	struct snd_info_entry *entry;
	const char *s = "trident";
	
	if (trident->device == TRIDENT_DEVICE_ID_SI7018)
		s = "sis7018";
	if (! snd_card_proc_new(trident->card, s, &entry))
		snd_info_set_text_ops(entry, trident, snd_trident_proc_read);
}