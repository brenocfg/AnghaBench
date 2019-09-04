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
struct snd_rawmidi_info {int dummy; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int __snd_rawmidi_info_select (struct snd_card*,struct snd_rawmidi_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 

int snd_rawmidi_info_select(struct snd_card *card, struct snd_rawmidi_info *info)
{
	int ret;

	mutex_lock(&register_mutex);
	ret = __snd_rawmidi_info_select(card, info);
	mutex_unlock(&register_mutex);
	return ret;
}