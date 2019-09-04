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
struct snd_efw {int /*<<< orphan*/  mutex; struct snd_efw* resp_buf; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_unit_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_efw*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_efw_stream_destroy_duplex (struct snd_efw*) ; 
 int /*<<< orphan*/  snd_efw_transaction_remove_instance (struct snd_efw*) ; 

__attribute__((used)) static void efw_free(struct snd_efw *efw)
{
	snd_efw_stream_destroy_duplex(efw);
	snd_efw_transaction_remove_instance(efw);
	fw_unit_put(efw->unit);

	kfree(efw->resp_buf);

	mutex_destroy(&efw->mutex);
	kfree(efw);
}