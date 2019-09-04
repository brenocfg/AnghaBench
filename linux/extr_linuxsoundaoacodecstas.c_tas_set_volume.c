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
typedef  int u8 ;
struct tas {int cached_volume_l; int cached_volume_r; scalar_t__ mute_r; scalar_t__ mute_l; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAS_REG_VOL ; 
 int* tas_gaintable ; 
 int /*<<< orphan*/  tas_write_reg (struct tas*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void tas_set_volume(struct tas *tas)
{
	u8 block[6];
	int tmp;
	u8 left, right;

	left = tas->cached_volume_l;
	right = tas->cached_volume_r;

	if (left > 177) left = 177;
	if (right > 177) right = 177;

	if (tas->mute_l) left = 0;
	if (tas->mute_r) right = 0;

	/* analysing the volume and mixer tables shows
	 * that they are similar enough when we shift
	 * the mixer table down by 4 bits. The error
	 * is miniscule, in just one item the error
	 * is 1, at a value of 0x07f17b (mixer table
	 * value is 0x07f17a) */
	tmp = tas_gaintable[left];
	block[0] = tmp>>20;
	block[1] = tmp>>12;
	block[2] = tmp>>4;
	tmp = tas_gaintable[right];
	block[3] = tmp>>20;
	block[4] = tmp>>12;
	block[5] = tmp>>4;
	tas_write_reg(tas, TAS_REG_VOL, 6, block);
}