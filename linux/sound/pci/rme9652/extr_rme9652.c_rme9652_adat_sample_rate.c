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
struct snd_rme9652 {int dummy; } ;

/* Variables and functions */
 int RME9652_fs48 ; 
 int /*<<< orphan*/  RME9652_status_register ; 
 int rme9652_read (struct snd_rme9652*,int /*<<< orphan*/ ) ; 
 scalar_t__ rme9652_running_double_speed (struct snd_rme9652*) ; 

__attribute__((used)) static inline int rme9652_adat_sample_rate(struct snd_rme9652 *rme9652)
{
	if (rme9652_running_double_speed(rme9652)) {
		return (rme9652_read(rme9652, RME9652_status_register) &
			RME9652_fs48) ? 96000 : 88200;
	} else {
		return (rme9652_read(rme9652, RME9652_status_register) &
			RME9652_fs48) ? 48000 : 44100;
	}
}