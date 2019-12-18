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
typedef  int /*<<< orphan*/  u32 ;
struct wm_adsp_compr_buf {scalar_t__ host_buf_ptr; int /*<<< orphan*/  host_buf_mem_type; int /*<<< orphan*/  dsp; } ;

/* Variables and functions */
 int wm_adsp_read_data_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int wm_adsp_buffer_read(struct wm_adsp_compr_buf *buf,
				      unsigned int field_offset, u32 *data)
{
	return wm_adsp_read_data_word(buf->dsp, buf->host_buf_mem_type,
				      buf->host_buf_ptr + field_offset, data);
}