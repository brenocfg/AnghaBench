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
struct TYPE_3__ {size_t num; struct cf_def* array; } ;
struct cf_preprocessor {TYPE_1__ defines; } ;
struct TYPE_4__ {int /*<<< orphan*/  str; } ;
struct cf_def {TYPE_2__ name; } ;

/* Variables and functions */
 size_t INVALID_INDEX ; 
 scalar_t__ strref_cmp_strref (int /*<<< orphan*/ *,struct strref const*) ; 

__attribute__((used)) static inline size_t cf_preprocess_get_def_idx(struct cf_preprocessor *pp,
					       const struct strref *def_name)
{
	struct cf_def *array = pp->defines.array;
	size_t i;

	for (i = 0; i < pp->defines.num; i++) {
		struct cf_def *cur_def = array + i;

		if (strref_cmp_strref(&cur_def->name.str, def_name) == 0)
			return i;
	}

	return INVALID_INDEX;
}