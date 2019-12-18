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
struct snd_rme9652 {int control_register; int passthru; } ;

/* Variables and functions */
 int /*<<< orphan*/  RME9652_control_register ; 
 int RME9652_inp_0 ; 
 int RME9652_start_bit ; 
 int rme9652_encode_latency (int) ; 
 int /*<<< orphan*/  rme9652_reset_hw_pointer (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_set_thru (struct snd_rme9652*,int,int) ; 
 int /*<<< orphan*/  rme9652_stop (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_write (struct snd_rme9652*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rme9652_set_passthru(struct snd_rme9652 *rme9652, int onoff)
{
	if (onoff) {
		rme9652_set_thru(rme9652, -1, 1);

		/* we don't want interrupts, so do a
		   custom version of rme9652_start().
		*/

		rme9652->control_register =
			RME9652_inp_0 | 
			rme9652_encode_latency(7) |
			RME9652_start_bit;

		rme9652_reset_hw_pointer(rme9652);

		rme9652_write(rme9652, RME9652_control_register,
			      rme9652->control_register);
		rme9652->passthru = 1;
	} else {
		rme9652_set_thru(rme9652, -1, 0);
		rme9652_stop(rme9652);		
		rme9652->passthru = 0;
	}

	return 0;
}