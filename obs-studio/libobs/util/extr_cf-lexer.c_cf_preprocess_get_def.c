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
 size_t cf_preprocess_get_def_idx (struct cf_preprocessor*,struct strref const*) ; 

__attribute__((used)) static inline struct cf_def *
cf_preprocess_get_def(struct cf_preprocessor *pp, const struct strref *def_name)
{
	size_t idx = cf_preprocess_get_def_idx(pp, def_name);
	if (idx == INVALID_INDEX)
		return NULL;

	return pp->defines.array + idx;
}