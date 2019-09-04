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
struct snd_ca0106 {scalar_t__ port; scalar_t__ spdif_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPTURE_CONTROL ; 
 scalar_t__ GPIO ; 
 int /*<<< orphan*/  SPDIF_SELECT1 ; 
 int /*<<< orphan*/  SPDIF_SELECT2 ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int snd_ca0106_ptr_read (struct snd_ca0106*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ca0106_ptr_write (struct snd_ca0106*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ca0106_spdif_enable(struct snd_ca0106 *emu)
{
	unsigned int val;

	if (emu->spdif_enable) {
		/* Digital */
		snd_ca0106_ptr_write(emu, SPDIF_SELECT1, 0, 0xf);
		snd_ca0106_ptr_write(emu, SPDIF_SELECT2, 0, 0x0b000000);
		val = snd_ca0106_ptr_read(emu, CAPTURE_CONTROL, 0) & ~0x1000;
		snd_ca0106_ptr_write(emu, CAPTURE_CONTROL, 0, val);
		val = inl(emu->port + GPIO) & ~0x101;
		outl(val, emu->port + GPIO);

	} else {
		/* Analog */
		snd_ca0106_ptr_write(emu, SPDIF_SELECT1, 0, 0xf);
		snd_ca0106_ptr_write(emu, SPDIF_SELECT2, 0, 0x000f0000);
		val = snd_ca0106_ptr_read(emu, CAPTURE_CONTROL, 0) | 0x1000;
		snd_ca0106_ptr_write(emu, CAPTURE_CONTROL, 0, val);
		val = inl(emu->port + GPIO) | 0x101;
		outl(val, emu->port + GPIO);
	}
}