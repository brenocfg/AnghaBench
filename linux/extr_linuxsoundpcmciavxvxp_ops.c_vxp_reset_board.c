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
struct vx_core {int dummy; } ;
struct snd_vxpocket {scalar_t__ regDIALOG; scalar_t__ regCDSP; } ;

/* Variables and functions */
 struct snd_vxpocket* to_vxpocket (struct vx_core*) ; 

__attribute__((used)) static void vxp_reset_board(struct vx_core *_chip, int cold_reset)
{
	struct snd_vxpocket *chip = to_vxpocket(_chip);

	chip->regCDSP = 0;
	chip->regDIALOG = 0;
}