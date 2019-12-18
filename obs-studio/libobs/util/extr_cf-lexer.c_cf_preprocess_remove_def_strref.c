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
struct strref {int dummy; } ;
struct TYPE_2__ {struct cf_def* array; } ;
struct cf_preprocessor {TYPE_1__ defines; } ;
struct cf_def {int dummy; } ;

/* Variables and functions */
 size_t INVALID_INDEX ; 
 int /*<<< orphan*/  cf_def_free (struct cf_def*) ; 
 size_t cf_preprocess_get_def_idx (struct cf_preprocessor*,struct strref const*) ; 
 int /*<<< orphan*/  da_erase (TYPE_1__,size_t) ; 

__attribute__((used)) static inline void cf_preprocess_remove_def_strref(struct cf_preprocessor *pp,
						   const struct strref *ref)
{
	size_t def_idx = cf_preprocess_get_def_idx(pp, ref);
	if (def_idx != INVALID_INDEX) {
		struct cf_def *array = pp->defines.array;
		cf_def_free(array + def_idx);
		da_erase(pp->defines, def_idx);
	}
}