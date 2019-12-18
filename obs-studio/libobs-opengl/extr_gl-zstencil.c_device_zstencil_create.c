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
typedef  int /*<<< orphan*/  uint32_t ;
struct gs_zstencil_buffer {int /*<<< orphan*/ * device; int /*<<< orphan*/  attachment; int /*<<< orphan*/  format; } ;
typedef  struct gs_zstencil_buffer gs_zstencil_t ;
typedef  int /*<<< orphan*/  gs_device_t ;
typedef  enum gs_zstencil_format { ____Placeholder_gs_zstencil_format } gs_zstencil_format ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 struct gs_zstencil_buffer* bzalloc (int) ; 
 int /*<<< orphan*/  convert_zstencil_format (int) ; 
 int /*<<< orphan*/  get_attachment (int) ; 
 int /*<<< orphan*/  gl_init_zsbuffer (struct gs_zstencil_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_zstencil_destroy (struct gs_zstencil_buffer*) ; 

gs_zstencil_t *device_zstencil_create(gs_device_t *device, uint32_t width,
				      uint32_t height,
				      enum gs_zstencil_format format)
{
	struct gs_zstencil_buffer *zs;

	zs = bzalloc(sizeof(struct gs_zstencil_buffer));
	zs->format = convert_zstencil_format(format);
	zs->attachment = get_attachment(format);
	zs->device = device;

	if (!gl_init_zsbuffer(zs, width, height)) {
		blog(LOG_ERROR, "device_zstencil_create (GL) failed");
		gs_zstencil_destroy(zs);
		return NULL;
	}

	return zs;
}