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
struct snd_ff {int /*<<< orphan*/  mutex; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_unit_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_ff*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ff_stream_destroy_duplex (struct snd_ff*) ; 
 int /*<<< orphan*/  snd_ff_transaction_unregister (struct snd_ff*) ; 

__attribute__((used)) static void ff_free(struct snd_ff *ff)
{
	snd_ff_stream_destroy_duplex(ff);
	snd_ff_transaction_unregister(ff);

	fw_unit_put(ff->unit);

	mutex_destroy(&ff->mutex);
	kfree(ff);
}