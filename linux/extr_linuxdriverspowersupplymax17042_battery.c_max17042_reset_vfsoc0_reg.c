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
struct regmap {int dummy; } ;
struct max17042_chip {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX17042_VFSOC ; 
 int /*<<< orphan*/  MAX17042_VFSOC0 ; 
 int /*<<< orphan*/  MAX17042_VFSOC0Enable ; 
 int /*<<< orphan*/  VFSOC0_LOCK ; 
 int /*<<< orphan*/  VFSOC0_UNLOCK ; 
 int /*<<< orphan*/  max17042_write_verify_reg (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max17042_reset_vfsoc0_reg(struct max17042_chip *chip)
{
	unsigned int vfSoc;
	struct regmap *map = chip->regmap;

	regmap_read(map, MAX17042_VFSOC, &vfSoc);
	regmap_write(map, MAX17042_VFSOC0Enable, VFSOC0_UNLOCK);
	max17042_write_verify_reg(map, MAX17042_VFSOC0, vfSoc);
	regmap_write(map, MAX17042_VFSOC0Enable, VFSOC0_LOCK);
}