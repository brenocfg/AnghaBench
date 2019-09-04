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
 scalar_t__ snd_emu10k1x_ptr_read (struct emu10k1x*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned char mpu401_read(struct emu10k1x *emu, struct emu10k1x_midi *mpu, int idx)
{
	return (unsigned char)snd_emu10k1x_ptr_read(emu, mpu->port + idx, 0);
}