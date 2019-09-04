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
struct snd_monitor_file {int /*<<< orphan*/  list; int /*<<< orphan*/  shutdown_list; int /*<<< orphan*/ * disconnected_f_op; struct file* file; } ;
struct snd_card {int /*<<< orphan*/  files_lock; int /*<<< orphan*/  card_dev; int /*<<< orphan*/  files_list; scalar_t__ shutdown; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_monitor_file*) ; 
 struct snd_monitor_file* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int snd_card_file_add(struct snd_card *card, struct file *file)
{
	struct snd_monitor_file *mfile;

	mfile = kmalloc(sizeof(*mfile), GFP_KERNEL);
	if (mfile == NULL)
		return -ENOMEM;
	mfile->file = file;
	mfile->disconnected_f_op = NULL;
	INIT_LIST_HEAD(&mfile->shutdown_list);
	spin_lock(&card->files_lock);
	if (card->shutdown) {
		spin_unlock(&card->files_lock);
		kfree(mfile);
		return -ENODEV;
	}
	list_add(&mfile->list, &card->files_list);
	get_device(&card->card_dev);
	spin_unlock(&card->files_lock);
	return 0;
}