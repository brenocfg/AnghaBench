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
struct snd_tscm {int /*<<< orphan*/  mutex; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_unit_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_tscm*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_tscm_stream_destroy_duplex (struct snd_tscm*) ; 
 int /*<<< orphan*/  snd_tscm_transaction_unregister (struct snd_tscm*) ; 

__attribute__((used)) static void tscm_free(struct snd_tscm *tscm)
{
	snd_tscm_transaction_unregister(tscm);
	snd_tscm_stream_destroy_duplex(tscm);

	fw_unit_put(tscm->unit);

	mutex_destroy(&tscm->mutex);
	kfree(tscm);
}