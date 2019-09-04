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
struct snd_korg1212 {int dummy; } ;
struct snd_device {struct snd_korg1212* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  K1212_DEBUG_PRINTK (char*) ; 
 int snd_korg1212_free (struct snd_korg1212*) ; 

__attribute__((used)) static int snd_korg1212_dev_free(struct snd_device *device)
{
        struct snd_korg1212 *korg1212 = device->device_data;
        K1212_DEBUG_PRINTK("K1212_DEBUG: Freeing device\n");
	return snd_korg1212_free(korg1212);
}