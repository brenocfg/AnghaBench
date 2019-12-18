#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct graphics_subsystem {int dummy; } ;
struct TYPE_8__ {int (* device_create ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  device; TYPE_2__ exports; int /*<<< orphan*/  module; int /*<<< orphan*/  effect_mutex; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ graphics_t ;

/* Variables and functions */
 int GS_ERROR_FAIL ; 
 int GS_ERROR_MODULE_NOT_FOUND ; 
 int GS_SUCCESS ; 
 TYPE_1__* bzalloc (int) ; 
 int /*<<< orphan*/  graphics_init (TYPE_1__*) ; 
 int /*<<< orphan*/  gs_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  load_graphics_imports (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  os_dlopen (char const*) ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gs_create(graphics_t **pgraphics, const char *module, uint32_t adapter)
{
	int errcode = GS_ERROR_FAIL;

	graphics_t *graphics = bzalloc(sizeof(struct graphics_subsystem));
	pthread_mutex_init_value(&graphics->mutex);
	pthread_mutex_init_value(&graphics->effect_mutex);

	graphics->module = os_dlopen(module);
	if (!graphics->module) {
		errcode = GS_ERROR_MODULE_NOT_FOUND;
		goto error;
	}

	if (!load_graphics_imports(&graphics->exports, graphics->module,
				   module))
		goto error;

	errcode = graphics->exports.device_create(&graphics->device, adapter);
	if (errcode != GS_SUCCESS)
		goto error;

	if (!graphics_init(graphics)) {
		errcode = GS_ERROR_FAIL;
		goto error;
	}

	*pgraphics = graphics;
	return errcode;

error:
	gs_destroy(graphics);
	return errcode;
}