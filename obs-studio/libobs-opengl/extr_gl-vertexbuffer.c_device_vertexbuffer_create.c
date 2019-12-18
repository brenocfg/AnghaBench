#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct gs_vertex_buffer {int dynamic; int /*<<< orphan*/  num; struct gs_vb_data* data; int /*<<< orphan*/ * device; } ;
struct gs_vb_data {int /*<<< orphan*/  num; } ;
typedef  struct gs_vertex_buffer gs_vertbuffer_t ;
typedef  int /*<<< orphan*/  gs_device_t ;

/* Variables and functions */
 int GS_DYNAMIC ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 struct gs_vertex_buffer* bzalloc (int) ; 
 int /*<<< orphan*/  create_buffers (struct gs_vertex_buffer*) ; 
 int /*<<< orphan*/  gs_vertexbuffer_destroy (struct gs_vertex_buffer*) ; 

gs_vertbuffer_t *device_vertexbuffer_create(gs_device_t *device,
					    struct gs_vb_data *data,
					    uint32_t flags)
{
	struct gs_vertex_buffer *vb = bzalloc(sizeof(struct gs_vertex_buffer));
	vb->device = device;
	vb->data = data;
	vb->num = data->num;
	vb->dynamic = flags & GS_DYNAMIC;

	if (!create_buffers(vb)) {
		blog(LOG_ERROR, "device_vertexbuffer_create (GL) failed");
		gs_vertexbuffer_destroy(vb);
		return NULL;
	}

	return vb;
}