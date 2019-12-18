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
struct snd_ice1712 {int /*<<< orphan*/  spec; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * maya_controls ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int maya44_add_controls(struct snd_ice1712 *ice)
{
	int err, i;

	for (i = 0; i < ARRAY_SIZE(maya_controls); i++) {
		err = snd_ctl_add(ice->card, snd_ctl_new1(&maya_controls[i],
							  ice->spec));
		if (err < 0)
			return err;
	}
	return 0;
}