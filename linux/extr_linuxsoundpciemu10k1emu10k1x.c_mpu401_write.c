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
struct emu10k1x_midi {scalar_t__ port; } ;
struct emu10k1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_emu10k1x_ptr_write (struct emu10k1x*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mpu401_write(struct emu10k1x *emu, struct emu10k1x_midi *mpu, int data, int idx)
{
	snd_emu10k1x_ptr_write(emu, mpu->port + idx, 0, data);
}