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
struct snd_card {int dummy; } ;
struct pardevice {int dummy; } ;
struct mts64 {int current_midi_output_port; int current_midi_input_port; struct pardevice* pardev; struct snd_card* card; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mts64* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_mts64_create(struct snd_card *card,
			    struct pardevice *pardev,
			    struct mts64 **rchip)
{
	struct mts64 *mts;

	*rchip = NULL;

	mts = kzalloc(sizeof(struct mts64), GFP_KERNEL);
	if (mts == NULL) 
		return -ENOMEM;

	/* Init chip specific data */
	spin_lock_init(&mts->lock);
	mts->card = card;
	mts->pardev = pardev;
	mts->current_midi_output_port = -1;
	mts->current_midi_input_port = -1;

	*rchip = mts;

	return 0;
}