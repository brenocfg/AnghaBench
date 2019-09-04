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
struct snd_dice {int /*<<< orphan*/  mutex; int /*<<< orphan*/  unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_unit_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_dice*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dice_stream_destroy_duplex (struct snd_dice*) ; 
 int /*<<< orphan*/  snd_dice_transaction_destroy (struct snd_dice*) ; 

__attribute__((used)) static void dice_free(struct snd_dice *dice)
{
	snd_dice_stream_destroy_duplex(dice);
	snd_dice_transaction_destroy(dice);
	fw_unit_put(dice->unit);

	mutex_destroy(&dice->mutex);
	kfree(dice);
}