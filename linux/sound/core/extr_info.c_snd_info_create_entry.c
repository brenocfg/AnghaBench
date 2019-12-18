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
struct snd_info_entry {int mode; int /*<<< orphan*/  access; int /*<<< orphan*/  children; int /*<<< orphan*/  list; struct module* module; struct snd_info_entry* parent; int /*<<< orphan*/  content; int /*<<< orphan*/ * name; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SNDRV_INFO_CONTENT_TEXT ; 
 int S_IFREG ; 
 int /*<<< orphan*/  kfree (struct snd_info_entry*) ; 
 int /*<<< orphan*/ * kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct snd_info_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct snd_info_entry *
snd_info_create_entry(const char *name, struct snd_info_entry *parent,
		      struct module *module)
{
	struct snd_info_entry *entry;
	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (entry == NULL)
		return NULL;
	entry->name = kstrdup(name, GFP_KERNEL);
	if (entry->name == NULL) {
		kfree(entry);
		return NULL;
	}
	entry->mode = S_IFREG | 0444;
	entry->content = SNDRV_INFO_CONTENT_TEXT;
	mutex_init(&entry->access);
	INIT_LIST_HEAD(&entry->children);
	INIT_LIST_HEAD(&entry->list);
	entry->parent = parent;
	entry->module = module;
	if (parent) {
		mutex_lock(&parent->access);
		list_add_tail(&entry->list, &parent->children);
		mutex_unlock(&parent->access);
	}
	return entry;
}