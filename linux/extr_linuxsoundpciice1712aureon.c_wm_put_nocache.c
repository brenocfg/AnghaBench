#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ subvendor; } ;
struct snd_ice1712 {TYPE_1__ eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUREON_WM_CS ; 
 int /*<<< orphan*/  PRODIGY_WM_CS ; 
 scalar_t__ VT1724_SUBDEVICE_PRODIGY71LT ; 
 scalar_t__ VT1724_SUBDEVICE_PRODIGY71XT ; 
 int /*<<< orphan*/  aureon_spi_write (struct snd_ice1712*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void wm_put_nocache(struct snd_ice1712 *ice, int reg, unsigned short val)
{
	aureon_spi_write(ice,
			 ((ice->eeprom.subvendor == VT1724_SUBDEVICE_PRODIGY71LT ||
			   ice->eeprom.subvendor == VT1724_SUBDEVICE_PRODIGY71XT) ?
			 PRODIGY_WM_CS : AUREON_WM_CS),
			(reg << 9) | (val & 0x1ff), 16);
}