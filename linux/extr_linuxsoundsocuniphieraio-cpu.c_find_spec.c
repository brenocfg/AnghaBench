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
struct uniphier_aio_spec {int dummy; } ;
struct uniphier_aio_chip_spec {int num_specs; struct uniphier_aio_spec* specs; } ;
struct uniphier_aio {TYPE_1__* chip; } ;
struct TYPE_2__ {struct uniphier_aio_chip_spec* chip_spec; } ;

/* Variables and functions */
 scalar_t__ match_spec (struct uniphier_aio_spec const*,char const*,int) ; 

__attribute__((used)) static const struct uniphier_aio_spec *find_spec(struct uniphier_aio *aio,
						 const char *name,
						 int direction)
{
	const struct uniphier_aio_chip_spec *chip_spec = aio->chip->chip_spec;
	int i;

	for (i = 0; i < chip_spec->num_specs; i++) {
		const struct uniphier_aio_spec *spec = &chip_spec->specs[i];

		if (match_spec(spec, name, direction))
			return spec;
	}

	return NULL;
}