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
struct rt5682_priv {int sysclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int const) ; 

__attribute__((used)) static int rt5682_div_sel(struct rt5682_priv *rt5682,
			  int target, const int div[], int size)
{
	int i;

	if (rt5682->sysclk < target) {
		pr_err("sysclk rate %d is too low\n",
			rt5682->sysclk);
		return 0;
	}

	for (i = 0; i < size - 1; i++) {
		pr_info("div[%d]=%d\n", i, div[i]);
		if (target * div[i] == rt5682->sysclk)
			return i;
		if (target * div[i + 1] > rt5682->sysclk) {
			pr_err("can't find div for sysclk %d\n",
				rt5682->sysclk);
			return i;
		}
	}

	if (target * div[i] < rt5682->sysclk)
		pr_err("sysclk rate %d is too high\n",
			rt5682->sysclk);

	return size - 1;

}