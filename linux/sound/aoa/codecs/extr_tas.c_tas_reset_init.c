#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_9__ {TYPE_3__* gpio; } ;
struct tas {int acr; int /*<<< orphan*/  bass; int /*<<< orphan*/  treble; TYPE_2__ codec; } ;
struct TYPE_10__ {TYPE_1__* methods; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* all_amps_restore ) (TYPE_3__*) ;int /*<<< orphan*/  (* set_hw_reset ) (TYPE_3__*,int) ;int /*<<< orphan*/  (* all_amps_off ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  TAS3004_BASS_ZERO ; 
 int /*<<< orphan*/  TAS3004_TREBLE_ZERO ; 
 int TAS_ACR_ANALOG_PDOWN ; 
 int TAS_MCS_SCLK64 ; 
 int TAS_MCS_SPORT_MODE_I2S ; 
 int TAS_MCS_SPORT_WL_24BIT ; 
 int /*<<< orphan*/  TAS_REG_ACR ; 
 int /*<<< orphan*/  TAS_REG_MCS ; 
 int /*<<< orphan*/  TAS_REG_MCS2 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*) ; 
 int /*<<< orphan*/  tas3004_set_drc (struct tas*) ; 
 int /*<<< orphan*/  tas_set_bass (struct tas*) ; 
 int /*<<< orphan*/  tas_set_treble (struct tas*) ; 
 scalar_t__ tas_write_reg (struct tas*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int tas_reset_init(struct tas *tas)
{
	u8 tmp;

	tas->codec.gpio->methods->all_amps_off(tas->codec.gpio);
	msleep(5);
	tas->codec.gpio->methods->set_hw_reset(tas->codec.gpio, 0);
	msleep(5);
	tas->codec.gpio->methods->set_hw_reset(tas->codec.gpio, 1);
	msleep(20);
	tas->codec.gpio->methods->set_hw_reset(tas->codec.gpio, 0);
	msleep(10);
	tas->codec.gpio->methods->all_amps_restore(tas->codec.gpio);

	tmp = TAS_MCS_SCLK64 | TAS_MCS_SPORT_MODE_I2S | TAS_MCS_SPORT_WL_24BIT;
	if (tas_write_reg(tas, TAS_REG_MCS, 1, &tmp))
		goto outerr;

	tas->acr |= TAS_ACR_ANALOG_PDOWN;
	if (tas_write_reg(tas, TAS_REG_ACR, 1, &tas->acr))
		goto outerr;

	tmp = 0;
	if (tas_write_reg(tas, TAS_REG_MCS2, 1, &tmp))
		goto outerr;

	tas3004_set_drc(tas);

	/* Set treble & bass to 0dB */
	tas->treble = TAS3004_TREBLE_ZERO;
	tas->bass = TAS3004_BASS_ZERO;
	tas_set_treble(tas);
	tas_set_bass(tas);

	tas->acr &= ~TAS_ACR_ANALOG_PDOWN;
	if (tas_write_reg(tas, TAS_REG_ACR, 1, &tas->acr))
		goto outerr;

	return 0;
 outerr:
	return -ENODEV;
}