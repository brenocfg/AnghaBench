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
struct TYPE_2__ {int id; } ;
struct tps6586x_regulator {TYPE_1__ desc; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tps6586x_regulator*) ; 
#define  TPS658623 132 
#define  TPS658624 131 
#define  TPS658640 130 
#define  TPS658640v2 129 
#define  TPS658643 128 
 struct tps6586x_regulator* tps658623_regulator ; 
 struct tps6586x_regulator* tps658640_regulator ; 
 struct tps6586x_regulator* tps658643_regulator ; 
 struct tps6586x_regulator* tps6586x_regulator ; 

__attribute__((used)) static struct tps6586x_regulator *find_regulator_info(int id, int version)
{
	struct tps6586x_regulator *ri;
	struct tps6586x_regulator *table = NULL;
	int num;
	int i;

	switch (version) {
	case TPS658623:
	case TPS658624:
		table = tps658623_regulator;
		num = ARRAY_SIZE(tps658623_regulator);
		break;
	case TPS658640:
	case TPS658640v2:
		table = tps658640_regulator;
		num = ARRAY_SIZE(tps658640_regulator);
		break;
	case TPS658643:
		table = tps658643_regulator;
		num = ARRAY_SIZE(tps658643_regulator);
		break;
	}

	/* Search version specific table first */
	if (table) {
		for (i = 0; i < num; i++) {
			ri = &table[i];
			if (ri->desc.id == id)
				return ri;
		}
	}

	for (i = 0; i < ARRAY_SIZE(tps6586x_regulator); i++) {
		ri = &tps6586x_regulator[i];
		if (ri->desc.id == id)
			return ri;
	}
	return NULL;
}