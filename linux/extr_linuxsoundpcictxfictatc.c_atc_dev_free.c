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
struct snd_device {struct ct_atc* device_data; } ;
struct ct_atc {int dummy; } ;

/* Variables and functions */
 int ct_atc_destroy (struct ct_atc*) ; 

__attribute__((used)) static int atc_dev_free(struct snd_device *dev)
{
	struct ct_atc *atc = dev->device_data;
	return ct_atc_destroy(atc);
}