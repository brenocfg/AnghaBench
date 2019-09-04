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
 int /*<<< orphan*/  PHASE28_WM_CS ; 
 int /*<<< orphan*/  phase28_spi_write (struct snd_ice1712*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void wm_put_nocache(struct snd_ice1712 *ice, int reg, unsigned short val)
{
	phase28_spi_write(ice, PHASE28_WM_CS, (reg << 9) | (val & 0x1ff), 16);
}