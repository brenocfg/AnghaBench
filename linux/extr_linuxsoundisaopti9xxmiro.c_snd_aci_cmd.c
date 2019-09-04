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
struct snd_miro_aci {int /*<<< orphan*/  aci_mutex; } ;

/* Variables and functions */
 int EINTR ; 
 int aci_read (struct snd_miro_aci*) ; 
 int aci_write (struct snd_miro_aci*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int snd_aci_cmd(struct snd_miro_aci *aci, int write1, int write2, int write3)
{
	int write[] = {write1, write2, write3};
	int value, i;

	if (mutex_lock_interruptible(&aci->aci_mutex))
		return -EINTR;

	for (i=0; i<3; i++) {
		if (write[i]< 0 || write[i] > 255)
			break;
		else {
			value = aci_write(aci, write[i]);
			if (value < 0)
				goto out;
		}
	}

	value = aci_read(aci);

out:	mutex_unlock(&aci->aci_mutex);
	return value;
}