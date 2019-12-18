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
struct vx_core {int irq; struct snd_card* card; int /*<<< orphan*/  mixer_mutex; struct snd_vx_ops* ops; int /*<<< orphan*/  type; struct snd_vx_hardware* hw; int /*<<< orphan*/  lock; } ;
struct snd_vx_ops {int dummy; } ;
struct snd_vx_hardware {char* name; int /*<<< orphan*/  type; } ;
struct snd_card {int /*<<< orphan*/  shortname; int /*<<< orphan*/  driver; struct vx_core* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vx_core* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vx_proc_init (struct vx_core*) ; 

struct vx_core *snd_vx_create(struct snd_card *card, struct snd_vx_hardware *hw,
			      struct snd_vx_ops *ops,
			      int extra_size)
{
	struct vx_core *chip;

	if (snd_BUG_ON(!card || !hw || !ops))
		return NULL;

	chip = kzalloc(sizeof(*chip) + extra_size, GFP_KERNEL);
	if (! chip)
		return NULL;
	mutex_init(&chip->lock);
	chip->irq = -1;
	chip->hw = hw;
	chip->type = hw->type;
	chip->ops = ops;
	mutex_init(&chip->mixer_mutex);

	chip->card = card;
	card->private_data = chip;
	strcpy(card->driver, hw->name);
	sprintf(card->shortname, "Digigram %s", hw->name);

	vx_proc_init(chip);

	return chip;
}