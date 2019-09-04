#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct fbcon_ops {unsigned int cursor_size; int* cursor_src; } ;
struct TYPE_4__ {int scan_align; int buf_align; } ;
struct fb_info {scalar_t__ state; TYPE_1__* fbops; TYPE_2__ pixmap; struct fbcon_ops* fbcon_par; } ;
struct fb_image {int width; unsigned int height; int* data; } ;
struct fb_cursor {int rop; int* mask; scalar_t__ enable; struct fb_image image; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fb_imageblit ) (struct fb_info*,struct fb_image*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FBINFO_STATE_RUNNING ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  ROP_COPY 129 
#define  ROP_XOR 128 
 int* fb_get_buffer_offset (struct fb_info*,TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  fb_pad_aligned_buffer (int*,unsigned int,int*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_image*) ; 

int soft_cursor(struct fb_info *info, struct fb_cursor *cursor)
{
	struct fbcon_ops *ops = info->fbcon_par;
	unsigned int scan_align = info->pixmap.scan_align - 1;
	unsigned int buf_align = info->pixmap.buf_align - 1;
	unsigned int i, size, dsize, s_pitch, d_pitch;
	struct fb_image *image;
	u8 *src, *dst;

	if (info->state != FBINFO_STATE_RUNNING)
		return 0;

	s_pitch = (cursor->image.width + 7) >> 3;
	dsize = s_pitch * cursor->image.height;

	if (dsize + sizeof(struct fb_image) != ops->cursor_size) {
		kfree(ops->cursor_src);
		ops->cursor_size = dsize + sizeof(struct fb_image);

		ops->cursor_src = kmalloc(ops->cursor_size, GFP_ATOMIC);
		if (!ops->cursor_src) {
			ops->cursor_size = 0;
			return -ENOMEM;
		}
	}

	src = ops->cursor_src + sizeof(struct fb_image);
	image = (struct fb_image *)ops->cursor_src;
	*image = cursor->image;
	d_pitch = (s_pitch + scan_align) & ~scan_align;

	size = d_pitch * image->height + buf_align;
	size &= ~buf_align;
	dst = fb_get_buffer_offset(info, &info->pixmap, size);

	if (cursor->enable) {
		switch (cursor->rop) {
		case ROP_XOR:
			for (i = 0; i < dsize; i++)
				src[i] = image->data[i] ^ cursor->mask[i];
			break;
		case ROP_COPY:
		default:
			for (i = 0; i < dsize; i++)
				src[i] = image->data[i] & cursor->mask[i];
			break;
		}
	} else
		memcpy(src, image->data, dsize);

	fb_pad_aligned_buffer(dst, d_pitch, src, s_pitch, image->height);
	image->data = dst;
	info->fbops->fb_imageblit(info, image);
	return 0;
}