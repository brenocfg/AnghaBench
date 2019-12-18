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
struct snd_pcm {int /*<<< orphan*/  card; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DEVICE_TYPE_PCM_CAPTURE ; 
 int /*<<< orphan*/  SNDRV_DEVICE_TYPE_PCM_PLAYBACK ; 
 int /*<<< orphan*/  S_ISCHR (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 scalar_t__ imajor (struct inode*) ; 
 unsigned int iminor (struct inode*) ; 
 int /*<<< orphan*/  snd_card_unref (int /*<<< orphan*/ ) ; 
 struct snd_pcm* snd_lookup_minor_data (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_major ; 

__attribute__((used)) static bool is_pcm_file(struct file *file)
{
	struct inode *inode = file_inode(file);
	struct snd_pcm *pcm;
	unsigned int minor;

	if (!S_ISCHR(inode->i_mode) || imajor(inode) != snd_major)
		return false;
	minor = iminor(inode);
	pcm = snd_lookup_minor_data(minor, SNDRV_DEVICE_TYPE_PCM_PLAYBACK);
	if (!pcm)
		pcm = snd_lookup_minor_data(minor, SNDRV_DEVICE_TYPE_PCM_CAPTURE);
	if (!pcm)
		return false;
	snd_card_unref(pcm->card);
	return true;
}