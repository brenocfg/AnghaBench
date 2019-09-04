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
struct snd_bebob {int /*<<< orphan*/  mutex; struct snd_bebob* maudio_special_quirk; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_unit_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_bebob*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_bebob_stream_destroy_duplex (struct snd_bebob*) ; 

__attribute__((used)) static void bebob_free(struct snd_bebob *bebob)
{
	snd_bebob_stream_destroy_duplex(bebob);
	fw_unit_put(bebob->unit);

	kfree(bebob->maudio_special_quirk);

	mutex_destroy(&bebob->mutex);
	kfree(bebob);
}