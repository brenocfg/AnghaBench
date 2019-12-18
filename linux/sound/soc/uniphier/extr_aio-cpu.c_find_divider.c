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
struct uniphier_aio_pll {int freq; } ;
struct uniphier_aio {TYPE_1__* chip; } ;
struct TYPE_2__ {struct uniphier_aio_pll* plls; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  is_valid_pll (TYPE_1__*,int) ; 

__attribute__((used)) static int find_divider(struct uniphier_aio *aio, int pll_id, unsigned int freq)
{
	struct uniphier_aio_pll *pll;
	int mul[] = { 1, 1, 1, 2, };
	int div[] = { 2, 3, 1, 3, };
	int i;

	if (!is_valid_pll(aio->chip, pll_id))
		return -EINVAL;

	pll = &aio->chip->plls[pll_id];
	for (i = 0; i < ARRAY_SIZE(mul); i++)
		if (pll->freq * mul[i] / div[i] == freq)
			return i;

	return -ENOTSUPP;
}