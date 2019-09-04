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
struct sfire_chip {struct pcm_runtime* pcm; } ;
struct pcm_runtime {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pcm_runtime*) ; 
 int /*<<< orphan*/  usb6fire_pcm_buffers_destroy (struct pcm_runtime*) ; 

void usb6fire_pcm_destroy(struct sfire_chip *chip)
{
	struct pcm_runtime *rt = chip->pcm;

	usb6fire_pcm_buffers_destroy(rt);
	kfree(rt);
	chip->pcm = NULL;
}