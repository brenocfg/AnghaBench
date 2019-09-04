#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct TYPE_3__ {int rate; int sr; int** divisors; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* rate_table ; 

__attribute__((used)) static inline int max98925_rate_value(struct snd_soc_component *component,
		int rate, int clock, int *value, int *n, int *m)
{
	int ret = -EINVAL;
	int i;

	for (i = 0; i < ARRAY_SIZE(rate_table); i++) {
		if (rate_table[i].rate >= rate) {
			*value = rate_table[i].sr;
			*n = rate_table[i].divisors[clock][0];
			*m = rate_table[i].divisors[clock][1];
			ret = 0;
			break;
		}
	}
	return ret;
}