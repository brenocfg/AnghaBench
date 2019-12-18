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
struct snd_rme9652 {int running; int /*<<< orphan*/  control_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  RME9652_ADAT1_INTERNAL ; 
 int /*<<< orphan*/  RME9652_control_register ; 
 int /*<<< orphan*/  rme9652_start (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_stop (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_write (struct snd_rme9652*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rme9652_set_adat1_input(struct snd_rme9652 *rme9652, int internal)
{
	int restart = 0;

	if (internal) {
		rme9652->control_register |= RME9652_ADAT1_INTERNAL;
	} else {
		rme9652->control_register &= ~RME9652_ADAT1_INTERNAL;
	}

	/* XXX do we actually need to stop the card when we do this ? */

	if ((restart = rme9652->running)) {
		rme9652_stop(rme9652);
	}

	rme9652_write(rme9652, RME9652_control_register, rme9652->control_register);

	if (restart) {
		rme9652_start(rme9652);
	}

	return 0;
}