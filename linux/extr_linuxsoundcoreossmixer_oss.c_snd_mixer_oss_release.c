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
struct snd_mixer_oss_file {TYPE_1__* card; } ;
struct inode {int dummy; } ;
struct file {struct snd_mixer_oss_file* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_mixer_oss_file*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_file_remove (TYPE_1__*,struct file*) ; 

__attribute__((used)) static int snd_mixer_oss_release(struct inode *inode, struct file *file)
{
	struct snd_mixer_oss_file *fmixer;

	if (file->private_data) {
		fmixer = file->private_data;
		module_put(fmixer->card->module);
		snd_card_file_remove(fmixer->card, file);
		kfree(fmixer);
	}
	return 0;
}