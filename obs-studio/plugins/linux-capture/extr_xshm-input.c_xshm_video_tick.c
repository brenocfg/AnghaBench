#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_xfixes_get_cursor_image_reply_t ;
typedef  int /*<<< orphan*/  xcb_xfixes_get_cursor_image_cookie_t ;
typedef  int /*<<< orphan*/  xcb_shm_get_image_reply_t ;
typedef  int /*<<< orphan*/  xcb_shm_get_image_cookie_t ;
struct TYPE_6__ {int width; int /*<<< orphan*/  cursor; TYPE_2__* xshm; int /*<<< orphan*/  texture; int /*<<< orphan*/  xcb; int /*<<< orphan*/  height; int /*<<< orphan*/  y_org; int /*<<< orphan*/  x_org; TYPE_1__* xcb_screen; int /*<<< orphan*/  source; } ;
struct TYPE_5__ {scalar_t__ data; int /*<<< orphan*/  seg; } ;
struct TYPE_4__ {int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (float) ; 
 int /*<<< orphan*/  XCB_IMAGE_FORMAT_Z_PIXMAP ; 
 int /*<<< orphan*/  XSHM_DATA (void*) ; 
 TYPE_3__* data ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_texture_set_image (int /*<<< orphan*/ ,void*,int,int) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 int /*<<< orphan*/  obs_source_showing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_shm_get_image_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_shm_get_image_unchecked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_xcursor_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_xfixes_get_cursor_image_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_xfixes_get_cursor_image_unchecked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xshm_video_tick(void *vptr, float seconds)
{
	UNUSED_PARAMETER(seconds);
	XSHM_DATA(vptr);

	if (!data->texture)
		return;
	if (!obs_source_showing(data->source))
		return;

	xcb_shm_get_image_cookie_t img_c;
	xcb_shm_get_image_reply_t *img_r;
	xcb_xfixes_get_cursor_image_cookie_t cur_c;
	xcb_xfixes_get_cursor_image_reply_t *cur_r;

	img_c = xcb_shm_get_image_unchecked(data->xcb, data->xcb_screen->root,
					    data->x_org, data->y_org,
					    data->width, data->height, ~0,
					    XCB_IMAGE_FORMAT_Z_PIXMAP,
					    data->xshm->seg, 0);
	cur_c = xcb_xfixes_get_cursor_image_unchecked(data->xcb);

	img_r = xcb_shm_get_image_reply(data->xcb, img_c, NULL);
	cur_r = xcb_xfixes_get_cursor_image_reply(data->xcb, cur_c, NULL);

	if (!img_r)
		goto exit;

	obs_enter_graphics();

	gs_texture_set_image(data->texture, (void *)data->xshm->data,
			     data->width * 4, false);
	xcb_xcursor_update(data->cursor, cur_r);

	obs_leave_graphics();

exit:
	free(img_r);
	free(cur_r);
}