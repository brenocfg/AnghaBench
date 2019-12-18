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
struct snd_card {struct portman* private_data; } ;
struct portman {struct pardevice* pardev; } ;
struct pardevice {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  parport_release (struct pardevice*) ; 
 int /*<<< orphan*/  parport_unregister_device (struct pardevice*) ; 
 int /*<<< orphan*/  portman_free (struct portman*) ; 

__attribute__((used)) static void snd_portman_card_private_free(struct snd_card *card)
{
	struct portman *pm = card->private_data;
	struct pardevice *pardev = pm->pardev;

	if (pardev) {
		parport_release(pardev);
		parport_unregister_device(pardev);
	}

	portman_free(pm);
}