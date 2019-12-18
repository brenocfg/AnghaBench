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
 int RME9652_Master ; 
 int RME9652_wsel ; 

__attribute__((used)) static int rme9652_sync_mode(struct snd_rme9652 *rme9652)
{
	if (rme9652->control_register & RME9652_wsel) {
		return 2;
	} else if (rme9652->control_register & RME9652_Master) {
		return 1;
	} else {
		return 0;
	}
}