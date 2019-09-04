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
typedef  int u8 ;
struct TYPE_2__ {int id; } ;
struct da9052_regulator_info {TYPE_1__ reg_desc; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct da9052_regulator_info*) ; 
#define  DA9052 132 
#define  DA9053_AA 131 
#define  DA9053_BA 130 
#define  DA9053_BB 129 
#define  DA9053_BC 128 
 struct da9052_regulator_info* da9052_regulator_info ; 
 struct da9052_regulator_info* da9053_regulator_info ; 

__attribute__((used)) static inline struct da9052_regulator_info *find_regulator_info(u8 chip_id,
								 int id)
{
	struct da9052_regulator_info *info;
	int i;

	switch (chip_id) {
	case DA9052:
		for (i = 0; i < ARRAY_SIZE(da9052_regulator_info); i++) {
			info = &da9052_regulator_info[i];
			if (info->reg_desc.id == id)
				return info;
		}
		break;
	case DA9053_AA:
	case DA9053_BA:
	case DA9053_BB:
	case DA9053_BC:
		for (i = 0; i < ARRAY_SIZE(da9053_regulator_info); i++) {
			info = &da9053_regulator_info[i];
			if (info->reg_desc.id == id)
				return info;
		}
		break;
	}

	return NULL;
}