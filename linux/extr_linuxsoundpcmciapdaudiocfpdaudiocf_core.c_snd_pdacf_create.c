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
struct snd_pdacf {int /*<<< orphan*/  ak4117_lock; int /*<<< orphan*/  reg_lock; struct snd_card* card; } ;
struct snd_card {struct snd_pdacf* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct snd_pdacf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdacf_proc_init (struct snd_pdacf*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct snd_pdacf *snd_pdacf_create(struct snd_card *card)
{
	struct snd_pdacf *chip;

	chip = kzalloc(sizeof(*chip), GFP_KERNEL);
	if (chip == NULL)
		return NULL;
	chip->card = card;
	mutex_init(&chip->reg_lock);
	spin_lock_init(&chip->ak4117_lock);
	card->private_data = chip;

	pdacf_proc_init(chip);
	return chip;
}