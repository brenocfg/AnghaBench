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
struct snd_info_entry {int mode; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int S_IFDIR ; 
 struct snd_info_entry* snd_info_create_module_entry (struct module*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_info_free_entry (struct snd_info_entry*) ; 
 scalar_t__ snd_info_register (struct snd_info_entry*) ; 

__attribute__((used)) static struct snd_info_entry *create_subdir(struct module *mod,
					    const char *name)
{
	struct snd_info_entry *entry;

	entry = snd_info_create_module_entry(mod, name, NULL);
	if (!entry)
		return NULL;
	entry->mode = S_IFDIR | 0555;
	if (snd_info_register(entry) < 0) {
		snd_info_free_entry(entry);
		return NULL;
	}
	return entry;
}