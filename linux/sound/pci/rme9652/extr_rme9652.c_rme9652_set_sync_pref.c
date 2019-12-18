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
#define  RME9652_SYNC_FROM_ADAT1 131 
#define  RME9652_SYNC_FROM_ADAT2 130 
#define  RME9652_SYNC_FROM_ADAT3 129 
#define  RME9652_SYNC_FROM_SPDIF 128 
 int /*<<< orphan*/  RME9652_SyncPref_ADAT1 ; 
 int /*<<< orphan*/  RME9652_SyncPref_ADAT2 ; 
 int /*<<< orphan*/  RME9652_SyncPref_ADAT3 ; 
 int /*<<< orphan*/  RME9652_SyncPref_Mask ; 
 int /*<<< orphan*/  RME9652_SyncPref_SPDIF ; 
 int /*<<< orphan*/  RME9652_control_register ; 
 int /*<<< orphan*/  rme9652_start (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_stop (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_write (struct snd_rme9652*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rme9652_set_sync_pref(struct snd_rme9652 *rme9652, int pref)
{
	int restart;

	rme9652->control_register &= ~RME9652_SyncPref_Mask;
	switch (pref) {
	case RME9652_SYNC_FROM_ADAT1:
		rme9652->control_register |= RME9652_SyncPref_ADAT1;
		break;
	case RME9652_SYNC_FROM_ADAT2:
		rme9652->control_register |= RME9652_SyncPref_ADAT2;
		break;
	case RME9652_SYNC_FROM_ADAT3:
		rme9652->control_register |= RME9652_SyncPref_ADAT3;
		break;
	case RME9652_SYNC_FROM_SPDIF:
		rme9652->control_register |= RME9652_SyncPref_SPDIF;
		break;
	}

	if ((restart = rme9652->running)) {
		rme9652_stop(rme9652);
	}

	rme9652_write(rme9652, RME9652_control_register, rme9652->control_register);

	if (restart) {
		rme9652_start(rme9652);
	}

	return 0;
}