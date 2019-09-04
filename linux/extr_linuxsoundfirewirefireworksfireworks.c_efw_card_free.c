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
struct snd_efw {scalar_t__ card_index; } ;
struct snd_card {struct snd_efw* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devices_mutex ; 
 int /*<<< orphan*/  devices_used ; 
 int /*<<< orphan*/  efw_free (struct snd_efw*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
efw_card_free(struct snd_card *card)
{
	struct snd_efw *efw = card->private_data;

	if (efw->card_index >= 0) {
		mutex_lock(&devices_mutex);
		clear_bit(efw->card_index, devices_used);
		mutex_unlock(&devices_mutex);
	}

	efw_free(card->private_data);
}