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
struct snd_dg00x {int /*<<< orphan*/  mutex; scalar_t__ registered; int /*<<< orphan*/  dwork; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct snd_dg00x* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dg00x_stream_update_duplex (struct snd_dg00x*) ; 
 int /*<<< orphan*/  snd_dg00x_transaction_reregister (struct snd_dg00x*) ; 
 int /*<<< orphan*/  snd_fw_schedule_registration (struct fw_unit*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_dg00x_update(struct fw_unit *unit)
{
	struct snd_dg00x *dg00x = dev_get_drvdata(&unit->device);

	/* Postpone a workqueue for deferred registration. */
	if (!dg00x->registered)
		snd_fw_schedule_registration(unit, &dg00x->dwork);

	snd_dg00x_transaction_reregister(dg00x);

	/*
	 * After registration, userspace can start packet streaming, then this
	 * code block works fine.
	 */
	if (dg00x->registered) {
		mutex_lock(&dg00x->mutex);
		snd_dg00x_stream_update_duplex(dg00x);
		mutex_unlock(&dg00x->mutex);
	}
}