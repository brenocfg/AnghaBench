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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct vbva_mouse_pointer_shape {int result; int flags; int hot_X; int hot_y; int width; int height; int /*<<< orphan*/  data; } ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HGSMI_CH_VBVA ; 
 int VBOX_MOUSE_POINTER_SHAPE ; 
 int VBOX_MOUSE_POINTER_VISIBLE ; 
 int /*<<< orphan*/  VBVA_MOUSE_POINTER_SHAPE ; 
#define  VERR_NOT_SUPPORTED 130 
#define  VERR_NO_MEMORY 129 
#define  VINF_SUCCESS 128 
 struct vbva_mouse_pointer_shape* hgsmi_buffer_alloc (struct gen_pool*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hgsmi_buffer_free (struct gen_pool*,struct vbva_mouse_pointer_shape*) ; 
 int /*<<< orphan*/  hgsmi_buffer_submit (struct gen_pool*,struct vbva_mouse_pointer_shape*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int hgsmi_update_pointer_shape(struct gen_pool *ctx, u32 flags,
			       u32 hot_x, u32 hot_y, u32 width, u32 height,
			       u8 *pixels, u32 len)
{
	struct vbva_mouse_pointer_shape *p;
	u32 pixel_len = 0;
	int rc;

	if (flags & VBOX_MOUSE_POINTER_SHAPE) {
		/*
		 * Size of the pointer data:
		 * sizeof (AND mask) + sizeof (XOR_MASK)
		 */
		pixel_len = ((((width + 7) / 8) * height + 3) & ~3) +
			 width * 4 * height;
		if (pixel_len > len)
			return -EINVAL;

		/*
		 * If shape is supplied, then always create the pointer visible.
		 * See comments in 'vboxUpdatePointerShape'
		 */
		flags |= VBOX_MOUSE_POINTER_VISIBLE;
	}

	p = hgsmi_buffer_alloc(ctx, sizeof(*p) + pixel_len, HGSMI_CH_VBVA,
			       VBVA_MOUSE_POINTER_SHAPE);
	if (!p)
		return -ENOMEM;

	p->result = VINF_SUCCESS;
	p->flags = flags;
	p->hot_X = hot_x;
	p->hot_y = hot_y;
	p->width = width;
	p->height = height;
	if (pixel_len)
		memcpy(p->data, pixels, pixel_len);

	hgsmi_buffer_submit(ctx, p);

	switch (p->result) {
	case VINF_SUCCESS:
		rc = 0;
		break;
	case VERR_NO_MEMORY:
		rc = -ENOMEM;
		break;
	case VERR_NOT_SUPPORTED:
		rc = -EBUSY;
		break;
	default:
		rc = -EINVAL;
	}

	hgsmi_buffer_free(ctx, p);

	return rc;
}