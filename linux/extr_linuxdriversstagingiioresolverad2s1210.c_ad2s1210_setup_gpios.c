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
struct gpio {unsigned long member_1; char* member_2; int /*<<< orphan*/  member_0; } ;
struct ad2s1210_state {TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/ * res; int /*<<< orphan*/ * a; int /*<<< orphan*/  sample; scalar_t__ gpioin; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct gpio*) ; 
 unsigned long GPIOF_DIR_IN ; 
 unsigned long GPIOF_DIR_OUT ; 
 int gpio_request_array (struct gpio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad2s1210_setup_gpios(struct ad2s1210_state *st)
{
	unsigned long flags = st->pdata->gpioin ? GPIOF_DIR_IN : GPIOF_DIR_OUT;
	struct gpio ad2s1210_gpios[] = {
		{ st->pdata->sample, GPIOF_DIR_IN, "sample" },
		{ st->pdata->a[0], flags, "a0" },
		{ st->pdata->a[1], flags, "a1" },
		{ st->pdata->res[0], flags, "res0" },
		{ st->pdata->res[0], flags, "res1" },
	};

	return gpio_request_array(ad2s1210_gpios, ARRAY_SIZE(ad2s1210_gpios));
}