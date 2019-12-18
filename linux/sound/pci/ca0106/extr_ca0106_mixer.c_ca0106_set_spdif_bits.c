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
struct snd_ca0106 {int /*<<< orphan*/ * spdif_str_bits; } ;

/* Variables and functions */
 scalar_t__ SPCS0 ; 
 int /*<<< orphan*/  snd_ca0106_ptr_write (struct snd_ca0106*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ca0106_set_spdif_bits(struct snd_ca0106 *emu, int idx)
{
	snd_ca0106_ptr_write(emu, SPCS0 + idx, 0, emu->spdif_str_bits[idx]);
}