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
struct snd_motu {int /*<<< orphan*/  mutex; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_unit_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_motu*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_motu_stream_destroy_duplex (struct snd_motu*) ; 
 int /*<<< orphan*/  snd_motu_transaction_unregister (struct snd_motu*) ; 

__attribute__((used)) static void motu_free(struct snd_motu *motu)
{
	snd_motu_transaction_unregister(motu);

	snd_motu_stream_destroy_duplex(motu);
	fw_unit_put(motu->unit);

	mutex_destroy(&motu->mutex);
	kfree(motu);
}