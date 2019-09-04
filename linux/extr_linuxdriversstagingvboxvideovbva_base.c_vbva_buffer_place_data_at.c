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
typedef  void const u8 ;
typedef  size_t u32 ;
struct vbva_buffer {size_t data_len; void const* data; } ;
struct vbva_buf_ctx {struct vbva_buffer* vbva; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void const*,void const*,scalar_t__) ; 

__attribute__((used)) static void vbva_buffer_place_data_at(struct vbva_buf_ctx *vbva_ctx,
				      const void *p, u32 len, u32 offset)
{
	struct vbva_buffer *vbva = vbva_ctx->vbva;
	u32 bytes_till_boundary = vbva->data_len - offset;
	u8 *dst = &vbva->data[offset];
	s32 diff = len - bytes_till_boundary;

	if (diff <= 0) {
		/* Chunk will not cross buffer boundary. */
		memcpy(dst, p, len);
	} else {
		/* Chunk crosses buffer boundary. */
		memcpy(dst, p, bytes_till_boundary);
		memcpy(&vbva->data[0], (u8 *)p + bytes_till_boundary, diff);
	}
}