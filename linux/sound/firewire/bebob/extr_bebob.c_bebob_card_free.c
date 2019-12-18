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
struct snd_card {struct snd_bebob* private_data; } ;
struct snd_bebob {int /*<<< orphan*/  card_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devices_mutex ; 
 int /*<<< orphan*/  devices_used ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_bebob_stream_destroy_duplex (struct snd_bebob*) ; 

__attribute__((used)) static void
bebob_card_free(struct snd_card *card)
{
	struct snd_bebob *bebob = card->private_data;

	mutex_lock(&devices_mutex);
	clear_bit(bebob->card_index, devices_used);
	mutex_unlock(&devices_mutex);

	snd_bebob_stream_destroy_duplex(bebob);
}