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
struct snd_riptide {unsigned int device_id; scalar_t__ rmidi; struct cmdif* cif; scalar_t__ port; } ;
struct riptideport {int dummy; } ;
struct cmdif {struct riptideport* hwport; scalar_t__ is_reset; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SEND_SETDPLL (struct cmdif*) ; 
 int /*<<< orphan*/  SET_EMPUIRQ (struct riptideport*) ; 
 struct cmdif* kzalloc (int,int /*<<< orphan*/ ) ; 
 int riptide_reset (struct cmdif*,struct snd_riptide*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_riptide_initialize(struct snd_riptide *chip)
{
	struct cmdif *cif;
	unsigned int device_id;
	int err;

	if (snd_BUG_ON(!chip))
		return -EINVAL;

	cif = chip->cif;
	if (!cif) {
		if ((cif = kzalloc(sizeof(struct cmdif), GFP_KERNEL)) == NULL)
			return -ENOMEM;
		cif->hwport = (struct riptideport *)chip->port;
		spin_lock_init(&cif->lock);
		chip->cif = cif;
	}
	cif->is_reset = 0;
	if ((err = riptide_reset(cif, chip)) != 0)
		return err;
	device_id = chip->device_id;
	switch (device_id) {
	case 0x4310:
	case 0x4320:
	case 0x4330:
		snd_printdd("Modem enable?\n");
		SEND_SETDPLL(cif);
		break;
	}
	snd_printdd("Enabling MPU IRQs\n");
	if (chip->rmidi)
		SET_EMPUIRQ(cif->hwport);
	return err;
}