#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct gs_vb_data {int num; int num_tex; struct gs_tvertarray* tvarray; void* colors; void* tangents; void* normals; void* points; } ;
struct gs_tvertarray {int width; void* array; } ;
typedef  int /*<<< orphan*/  gs_vertbuffer_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* device_vertexbuffer_create ) (int /*<<< orphan*/ ,struct gs_vb_data*,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  device; TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;

/* Variables and functions */
 int GS_DUP_BUFFER ; 
 void* bmemdup (void*,size_t) ; 
 struct gs_tvertarray* bzalloc (int) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 struct gs_vb_data* gs_vbdata_create () ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,struct gs_vb_data*,int) ; 
 TYPE_2__* thread_graphics ; 

gs_vertbuffer_t *gs_vertexbuffer_create(struct gs_vb_data *data,
		uint32_t flags)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid("gs_vertexbuffer_create"))
		return NULL;

	if (data && data->num && (flags & GS_DUP_BUFFER) != 0) {
		struct gs_vb_data *new_data = gs_vbdata_create();

		new_data->num = data->num;

#define DUP_VAL(val) \
		do { \
			if (data->val) \
				new_data->val = bmemdup(data->val, \
						sizeof(*data->val) * \
						data->num); \
		} while (false)

		DUP_VAL(points);
		DUP_VAL(normals);
		DUP_VAL(tangents);
		DUP_VAL(colors);
#undef DUP_VAL

		if (data->tvarray && data->num_tex) {
			new_data->num_tex = data->num_tex;
			new_data->tvarray = bzalloc(
					sizeof(struct gs_tvertarray) *
					data->num_tex);

			for (size_t i = 0; i < data->num_tex; i++) {
				struct gs_tvertarray *tv = &data->tvarray[i];
				struct gs_tvertarray *new_tv =
					&new_data->tvarray[i];
				size_t size = tv->width * sizeof(float);

				new_tv->width = tv->width;
				new_tv->array = bmemdup(tv->array,
						size * data->num);
			}
		}

		data = new_data;
	}

	return graphics->exports.device_vertexbuffer_create(graphics->device,
			data, flags);
}