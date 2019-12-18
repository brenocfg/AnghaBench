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
 int RME9652_opt_out ; 

__attribute__((used)) static int rme9652_spdif_out(struct snd_rme9652 *rme9652)
{
	return (rme9652->control_register & RME9652_opt_out) ? 1 : 0;
}