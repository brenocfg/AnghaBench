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
struct snd_dg00x {int /*<<< orphan*/  mutex; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_unit_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_dg00x*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dg00x_stream_destroy_duplex (struct snd_dg00x*) ; 
 int /*<<< orphan*/  snd_dg00x_transaction_unregister (struct snd_dg00x*) ; 

__attribute__((used)) static void dg00x_free(struct snd_dg00x *dg00x)
{
	snd_dg00x_stream_destroy_duplex(dg00x);
	snd_dg00x_transaction_unregister(dg00x);

	fw_unit_put(dg00x->unit);

	mutex_destroy(&dg00x->mutex);
	kfree(dg00x);
}