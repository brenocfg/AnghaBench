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
struct snd_dg00x {int dummy; } ;
struct snd_card {struct snd_dg00x* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_dg00x_stream_destroy_duplex (struct snd_dg00x*) ; 
 int /*<<< orphan*/  snd_dg00x_transaction_unregister (struct snd_dg00x*) ; 

__attribute__((used)) static void dg00x_card_free(struct snd_card *card)
{
	struct snd_dg00x *dg00x = card->private_data;

	snd_dg00x_stream_destroy_duplex(dg00x);
	snd_dg00x_transaction_unregister(dg00x);
}