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
struct snd_card {int dummy; } ;
struct portman {struct pardevice* pardev; struct snd_card* card; int /*<<< orphan*/  reg_lock; } ;
struct pardevice {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct portman* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int portman_create(struct snd_card *card,
			  struct pardevice *pardev,
			  struct portman **rchip)
{
	struct portman *pm;

	*rchip = NULL;

	pm = kzalloc(sizeof(struct portman), GFP_KERNEL);
	if (pm == NULL) 
		return -ENOMEM;

	/* Init chip specific data */
	spin_lock_init(&pm->reg_lock);
	pm->card = card;
	pm->pardev = pardev;

	*rchip = pm;

	return 0;
}