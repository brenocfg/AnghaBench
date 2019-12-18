#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t num; } ;
struct TYPE_6__ {TYPE_1__ default_val; } ;
typedef  TYPE_2__ gs_eparam_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bzalloc (size_t) ; 
 int /*<<< orphan*/  effect_getdefaultval_inline (TYPE_2__*,void*,size_t) ; 

void *gs_effect_get_default_val(gs_eparam_t *param)
{
	if (!param) {
		blog(LOG_ERROR, "gs_effect_get_default_val: invalid param");
		return NULL;
	}
	size_t size = param->default_val.num;
	void *data;

	if (size)
		data = (void *)bzalloc(size);
	else
		return NULL;

	effect_getdefaultval_inline(param, data, size);

	return data;
}