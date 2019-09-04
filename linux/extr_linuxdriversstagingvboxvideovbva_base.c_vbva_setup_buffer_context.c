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
typedef  void* u32 ;
struct vbva_buf_ctx {void* buffer_length; void* buffer_offset; } ;

/* Variables and functions */

void vbva_setup_buffer_context(struct vbva_buf_ctx *vbva_ctx,
			       u32 buffer_offset, u32 buffer_length)
{
	vbva_ctx->buffer_offset = buffer_offset;
	vbva_ctx->buffer_length = buffer_length;
}