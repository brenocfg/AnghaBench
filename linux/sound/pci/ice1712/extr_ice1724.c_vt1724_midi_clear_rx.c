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
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICEREG1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPU_DATA ; 
 int /*<<< orphan*/  MPU_RXFIFO ; 
 unsigned int inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vt1724_midi_clear_rx(struct snd_ice1712 *ice)
{
	unsigned int count;

	for (count = inb(ICEREG1724(ice, MPU_RXFIFO)); count > 0; --count)
		inb(ICEREG1724(ice, MPU_DATA));
}