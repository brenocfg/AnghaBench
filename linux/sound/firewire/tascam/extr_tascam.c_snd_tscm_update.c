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
struct snd_tscm {int /*<<< orphan*/  mutex; scalar_t__ registered; int /*<<< orphan*/  dwork; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct snd_tscm* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_tscm_stream_update_duplex (struct snd_tscm*) ; 
 int /*<<< orphan*/  snd_tscm_transaction_reregister (struct snd_tscm*) ; 

__attribute__((used)) static void snd_tscm_update(struct fw_unit *unit)
{
	struct snd_tscm *tscm = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue for deferred registration. */
	if (!tscm->registered)
		snd_fw_schedule_registration(unit, &tscm->dwork);

	snd_tscm_transaction_reregister(tscm);

	/*
	 * After registration, userspace can start packet streaming, then this
	 * code block works fine.
	 */
	if (tscm->registered) {
		mutex_lock(&tscm->mutex);
		snd_tscm_stream_update_duplex(tscm);
		mutex_unlock(&tscm->mutex);
	}
}