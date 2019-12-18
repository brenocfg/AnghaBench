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
struct snd_device {struct atiixp* device_data; } ;
struct atiixp {int dummy; } ;

/* Variables and functions */
 int snd_atiixp_free (struct atiixp*) ; 

__attribute__((used)) static int snd_atiixp_dev_free(struct snd_device *device)
{
	struct atiixp *chip = device->device_data;
	return snd_atiixp_free(chip);
}