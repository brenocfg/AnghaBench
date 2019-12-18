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
struct snd_motu {int dummy; } ;
struct snd_card {struct snd_motu* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_motu_stream_destroy_duplex (struct snd_motu*) ; 
 int /*<<< orphan*/  snd_motu_transaction_unregister (struct snd_motu*) ; 

__attribute__((used)) static void motu_card_free(struct snd_card *card)
{
	struct snd_motu *motu = card->private_data;

	snd_motu_transaction_unregister(motu);
	snd_motu_stream_destroy_duplex(motu);
}