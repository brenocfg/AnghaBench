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
struct strref {int dummy; } ;
struct TYPE_3__ {size_t num; struct macro_param* array; } ;
struct macro_params {TYPE_1__ params; } ;
struct TYPE_4__ {int /*<<< orphan*/  str; } ;
struct macro_param {TYPE_2__ name; } ;

/* Variables and functions */
 scalar_t__ strref_cmp_strref (int /*<<< orphan*/ *,struct strref const*) ; 

__attribute__((used)) static inline struct macro_param *
get_macro_param(const struct macro_params *params, const struct strref *name)
{
	size_t i;
	if (!params)
		return NULL;

	for (i = 0; i < params->params.num; i++) {
		struct macro_param *param = params->params.array + i;
		if (strref_cmp_strref(&param->name.str, name) == 0)
			return param;
	}

	return NULL;
}