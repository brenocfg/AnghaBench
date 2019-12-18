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
struct snd_rme9652 {int control_register; } ;

/* Variables and functions */
 int RME9652_SYNC_FROM_ADAT1 ; 
 int RME9652_SYNC_FROM_ADAT2 ; 
 int RME9652_SYNC_FROM_ADAT3 ; 
 int RME9652_SYNC_FROM_SPDIF ; 
#define  RME9652_SyncPref_ADAT1 131 
#define  RME9652_SyncPref_ADAT2 130 
#define  RME9652_SyncPref_ADAT3 129 
 int RME9652_SyncPref_Mask ; 
#define  RME9652_SyncPref_SPDIF 128 

__attribute__((used)) static int rme9652_sync_pref(struct snd_rme9652 *rme9652)
{
	switch (rme9652->control_register & RME9652_SyncPref_Mask) {
	case RME9652_SyncPref_ADAT1:
		return RME9652_SYNC_FROM_ADAT1;
	case RME9652_SyncPref_ADAT2:
		return RME9652_SYNC_FROM_ADAT2;
	case RME9652_SyncPref_ADAT3:
		return RME9652_SYNC_FROM_ADAT3;
	case RME9652_SyncPref_SPDIF:
		return RME9652_SYNC_FROM_SPDIF;
	}
	/* Not reachable */
	return 0;
}