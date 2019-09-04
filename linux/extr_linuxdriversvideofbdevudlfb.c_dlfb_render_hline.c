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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  char u8 ;
typedef  int u32 ;
struct urb {char* transfer_buffer; int transfer_buffer_length; } ;
struct dlfb_data {int base16; int backing_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlfb_compress_hline (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int*,char**,char*,unsigned long,int*) ; 
 struct urb* dlfb_get_urb (struct dlfb_data*) ; 
 scalar_t__ dlfb_submit_urb (struct dlfb_data*,struct urb*,int) ; 
 scalar_t__ dlfb_trim_hline (char const*,char const**,int*) ; 

__attribute__((used)) static int dlfb_render_hline(struct dlfb_data *dlfb, struct urb **urb_ptr,
			      const char *front, char **urb_buf_ptr,
			      u32 byte_offset, u32 byte_width,
			      int *ident_ptr, int *sent_ptr)
{
	const u8 *line_start, *line_end, *next_pixel;
	u32 dev_addr = dlfb->base16 + byte_offset;
	struct urb *urb = *urb_ptr;
	u8 *cmd = *urb_buf_ptr;
	u8 *cmd_end = (u8 *) urb->transfer_buffer + urb->transfer_buffer_length;
	unsigned long back_buffer_offset = 0;

	line_start = (u8 *) (front + byte_offset);
	next_pixel = line_start;
	line_end = next_pixel + byte_width;

	if (dlfb->backing_buffer) {
		int offset;
		const u8 *back_start = (u8 *) (dlfb->backing_buffer
						+ byte_offset);

		back_buffer_offset = (unsigned long)back_start - (unsigned long)line_start;

		*ident_ptr += dlfb_trim_hline(back_start, &next_pixel,
			&byte_width);

		offset = next_pixel - line_start;
		line_end = next_pixel + byte_width;
		dev_addr += offset;
		back_start += offset;
		line_start += offset;
	}

	while (next_pixel < line_end) {

		dlfb_compress_hline((const uint16_t **) &next_pixel,
			     (const uint16_t *) line_end, &dev_addr,
			(u8 **) &cmd, (u8 *) cmd_end, back_buffer_offset,
			ident_ptr);

		if (cmd >= cmd_end) {
			int len = cmd - (u8 *) urb->transfer_buffer;
			if (dlfb_submit_urb(dlfb, urb, len))
				return 1; /* lost pixels is set */
			*sent_ptr += len;
			urb = dlfb_get_urb(dlfb);
			if (!urb)
				return 1; /* lost_pixels is set */
			*urb_ptr = urb;
			cmd = urb->transfer_buffer;
			cmd_end = &cmd[urb->transfer_buffer_length];
		}
	}

	*urb_buf_ptr = cmd;

	return 0;
}