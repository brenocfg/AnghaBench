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
struct snd_efw {int /*<<< orphan*/  unit; } ;
struct fw_device {int generation; int node_id; struct fw_card* card; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 unsigned int SNDRV_CARDS ; 
 int /*<<< orphan*/  copy_resp_to_buf (struct snd_efw*,void*,size_t,int*) ; 
 struct fw_device* fw_parent_device (int /*<<< orphan*/ ) ; 
 struct snd_efw** instances ; 
 int /*<<< orphan*/  instances_lock ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
handle_resp_for_user(struct fw_card *card, int generation, int source,
		     void *data, size_t length, int *rcode)
{
	struct fw_device *device;
	struct snd_efw *efw;
	unsigned int i;

	spin_lock_irq(&instances_lock);

	for (i = 0; i < SNDRV_CARDS; i++) {
		efw = instances[i];
		if (efw == NULL)
			continue;
		device = fw_parent_device(efw->unit);
		if ((device->card != card) ||
		    (device->generation != generation))
			continue;
		smp_rmb();	/* node id vs. generation */
		if (device->node_id != source)
			continue;

		break;
	}
	if (i == SNDRV_CARDS)
		goto end;

	copy_resp_to_buf(efw, data, length, rcode);
end:
	spin_unlock_irq(&instances_lock);
}