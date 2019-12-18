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
struct isight {int /*<<< orphan*/  unit; int /*<<< orphan*/  mutex; int /*<<< orphan*/  card; } ;
struct fw_unit {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct isight* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_unit_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isight_pcm_abort (struct isight*) ; 
 int /*<<< orphan*/  isight_stop_streaming (struct isight*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isight_remove(struct fw_unit *unit)
{
	struct isight *isight = dev_get_drvdata(&unit->device);

	isight_pcm_abort(isight);

	snd_card_disconnect(isight->card);

	mutex_lock(&isight->mutex);
	isight_stop_streaming(isight);
	mutex_unlock(&isight->mutex);

	// Block till all of ALSA character devices are released.
	snd_card_free(isight->card);

	mutex_destroy(&isight->mutex);
	fw_unit_put(isight->unit);
}