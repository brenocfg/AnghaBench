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
struct snd_trident {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  T4D_AINTEN_A ; 
 int /*<<< orphan*/  T4D_AINTEN_B ; 
 int /*<<< orphan*/  T4D_STOP_A ; 
 int /*<<< orphan*/  T4D_STOP_B ; 
 int /*<<< orphan*/  TRID_REG (struct snd_trident*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_trident_stop_all_voices(struct snd_trident *trident)
{
	outl(0xffffffff, TRID_REG(trident, T4D_STOP_A));
	outl(0xffffffff, TRID_REG(trident, T4D_STOP_B));
	outl(0, TRID_REG(trident, T4D_AINTEN_A));
	outl(0, TRID_REG(trident, T4D_AINTEN_B));
}