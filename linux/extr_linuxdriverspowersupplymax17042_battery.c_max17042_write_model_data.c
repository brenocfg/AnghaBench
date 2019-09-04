#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct regmap {int dummy; } ;
struct max17042_chip {TYPE_2__* pdata; struct regmap* regmap; } ;
struct TYPE_4__ {TYPE_1__* config_data; } ;
struct TYPE_3__ {int /*<<< orphan*/ * cell_char_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_write (struct regmap*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void max17042_write_model_data(struct max17042_chip *chip,
					u8 addr, int size)
{
	struct regmap *map = chip->regmap;
	int i;

	for (i = 0; i < size; i++)
		regmap_write(map, addr + i,
			chip->pdata->config_data->cell_char_tbl[i]);
}