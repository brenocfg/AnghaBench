#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t num; int /*<<< orphan*/  array; } ;
struct TYPE_4__ {int changed; TYPE_3__ cur_val; } ;
typedef  TYPE_1__ gs_eparam_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  da_resize (TYPE_3__,size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static inline void effect_setval_inline(gs_eparam_t *param, const void *data,
					size_t size)
{
	bool size_changed;

	if (!param) {
		blog(LOG_ERROR, "effect_setval_inline: invalid param");
		return;
	}

	if (!data) {
		blog(LOG_ERROR, "effect_setval_inline: invalid data");
		return;
	}

	size_changed = param->cur_val.num != size;

	if (size_changed)
		da_resize(param->cur_val, size);

	if (size_changed || memcmp(param->cur_val.array, data, size) != 0) {
		memcpy(param->cur_val.array, data, size);
		param->changed = true;
	}
}